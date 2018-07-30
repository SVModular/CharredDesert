#include "Carbon.hpp"

CarbonModule::CarbonModule()
    : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
}

void CarbonModule::step() {
  float audio_in = inputs[AUDIO_INPUT].value / 5.0f;
  frequency = clamp((inputs[FREQ_INPUT].active ? inputs[FREQ_INPUT].value * 1000 : 0) + params[FREQ_PARAM].value, 0.0f, 7000.0f);
  float res = clamp((inputs[REZ_INPUT].active ? inputs[REZ_INPUT].value / 10 : 0) + params[REZ_PARAM].value, 0.0f, 4.0f);

  filter.setSamplerate(engineGetSampleRate());
  filter.setCoefficients(frequency, res);

  float out = 0.0f;

  filter.process(&audio_in, &out, 1);

  outputs[AUDIO_OUTPUT].value = 5.0f * out;
}
