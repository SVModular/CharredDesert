#include "Carbon.hpp"

#include <cmath>
CarbonModule::CarbonModule()
    : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
  frequency = 0.0f;
  filter.clear();
}

void CarbonModule::step() {
  // update the display no matter what
  frequency = clamp((inputs[FREQ_INPUT].active ? inputs[FREQ_INPUT].value * 1000 : 0) + params[FREQ_PARAM].value, 20.0f, 6000.0f);

  if (inputs[AUDIO_INPUT].active && outputs[AUDIO_OUTPUT].active) {
    float audio_in = inputs[AUDIO_INPUT].value / 5.0f;
    float res = clamp((inputs[REZ_INPUT].active ? inputs[REZ_INPUT].value / 10 : 0) + params[REZ_PARAM].value, 0.1f, 4.0f);

    filter.setSamplerate(engineGetSampleRate());
    filter.setCoefficients(frequency, res);

    float out = 0.0f;

    filter.process(&audio_in, &out, 1);

    // filter can sometimes get unstable at high frequencies, if it does, reset
    if (isnan(out)) {
      out = 0.0f;
      filter.clear();
    }
    outputs[AUDIO_OUTPUT].value = 5.0f * out;
  } else {
    outputs[AUDIO_OUTPUT].value = 0.0f;
  }
}
