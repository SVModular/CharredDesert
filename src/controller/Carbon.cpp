#include "Carbon.hpp"

#include <cmath>

CarbonModule::CarbonModule() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  configParam(CarbonModule::FREQ_PARAM, 20.0f, 6000.0f, (6000 - 20) / 2);
  configParam(CarbonModule::REZ_PARAM, 0.0f, 4.0f, 2.0f);
  frequency = 0.0f;
  filter.clear();
}

void CarbonModule::process(const ProcessArgs &args) {
  // update the display no matter what
  frequency = clamp((inputs[FREQ_INPUT].isConnected() ? inputs[FREQ_INPUT].getVoltage() * 1000 : 0) + params[FREQ_PARAM].getValue(), 20.0f, 6000.0f);

  if (inputs[AUDIO_INPUT].isConnected() && outputs[AUDIO_OUTPUT].isConnected()) {
    float audio_in = inputs[AUDIO_INPUT].getVoltage() / 5.0f;
    float res = clamp((inputs[REZ_INPUT].isConnected() ? inputs[REZ_INPUT].getVoltage() / 10 : 0) + params[REZ_PARAM].getValue(), 0.1f, 4.0f);

    filter.setSamplerate(args.sampleRate);
    filter.setCoefficients(frequency, res);

    float out = 0.0f;

    filter.process(&audio_in, &out, 1);

    // filter can sometimes get unstable at high frequencies, if it does, reset
    if (isnan(out)) {
      out = 0.0f;
      filter.clear();
    }
    outputs[AUDIO_OUTPUT].setVoltage(5.0f * out);
  } else {
    outputs[AUDIO_OUTPUT].setVoltage(0.0f);
  }
}
