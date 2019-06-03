#include "Noise.hpp"

NoiseModule::NoiseModule() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  wn = new SynthDevKit::WhiteNoise(0);
  pn = new SynthDevKit::PinkNoise(0);
  cv = new SynthDevKit::CV(1.7f);

  configParam(NoiseModule::NOISE_SWITCH, 0.0, 1.0, 1.0);
}

void NoiseModule::process(const ProcessArgs &args) {
  float cv_in = inputs[CV_INPUT].getVoltage();

  cv->update(cv_in);

  if (cv->isHigh()) {
    if (params[NOISE_SWITCH].getValue()) {
      outputs[AUDIO_OUTPUT].setVoltage(wn->stepValue());
    } else {
      outputs[AUDIO_OUTPUT].setVoltage(pn->stepValue());
    }

    lights[ON_LED].value = 1;
  } else {
    outputs[AUDIO_OUTPUT].setVoltage(0);
    lights[ON_LED].value = 0;
  }
}
