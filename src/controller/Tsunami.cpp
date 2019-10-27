#include "Tsunami.hpp"


TsunamiModule::TsunamiModule() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);

  sampleRate = 44100;
  for (uint8_t i = 0; i < SHIFT_COUNT; i++) {
    configParam(TsunamiModule::LEVEL + i, 0.0f, 1.0f, 0.5f);
    configParam(TsunamiModule::SHIFT + i, 0.0f, 1.0f, float(i) / 10.0);

    delay[i].setMax(uint64_t(sampleRate / 10.0));
    uint64_t nDelay = uint64_t((sampleRate / 10.0) * (float(i) / 10.0));
    delay[i].setDelay(nDelay);
  }

  configParam(TsunamiModule::MASTER_LEVEL, 0.0f, 1.0f, 0.5f);

}

float TsunamiModule::paramValue (uint16_t param, uint16_t input, float low, float high) {
  float current = params[param].getValue();

  if (inputs[input].isConnected()) {
    // high - low, divided by one tenth input voltage, plus the current value
    current += ((inputs[input].getVoltage() / 10) * (high - low));
  }

  return clamp(current, low, high);
}

void TsunamiModule::process(const ProcessArgs &args) {
  if (sampleRate != args.sampleRate) {
    sampleRate = args.sampleRate;
    for (uint8_t i = 0; i < SHIFT_COUNT; i++) {
      delay[i].setMax(uint64_t(sampleRate / 10.0));
    }
  }

  float in = inputs[MASTER_IN].getVoltage();
  float master_level = params[MASTER_LEVEL].getValue();
  in *= master_level;

  float mix = 0.0f;
  for (int i = 0; i < SHIFT_COUNT; i++) {
    float level = params[LEVEL + i].getValue();
    float shift = paramValue(SHIFT + i, CV + i, 0.0, 1);
    uint64_t nDelay = uint64_t((sampleRate / 10.0) * shift);
    if (nDelay != delay[i].delay) {
      delay[i].setDelay(nDelay);
    }

    float out = delay[i].step(in);

    mix += (out * level);

    outputs[OUT + i].setVoltage(mix);
    outputs[POLY_OUT].setVoltage(out * level, i);
  }

  outputs[MASTER_OUT].setVoltage(mix);
  outputs[POLY_OUT].setChannels(SHIFT_COUNT);
}
