#include "Oscar.hpp"

static float calculateMix(float input, float param) {
  return clamp((input + param), 0.0f, 10.0f);
}

static float calculateFrequency(float voltage) {
  return 261.626f * powf(2.0f, voltage);
}

OscarModule::OscarModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
  osc = new LowFrequencyOscillator();
}

void OscarModule::step() {
  float freq = inputs[FREQ_INPUT].value;

  osc->setPitch(calculateFrequency(freq));
  osc->step(engineGetSampleTime());

  outputs[AUDIO_OUTPUT1].value = 5.0f * ((osc->sin() * ((10 - calculateMix(inputs[MIX_INPUT1].value, params[MIX_PARAM1].value)) / 10) + (osc->tri() * (calculateMix(inputs[MIX_INPUT1]. value, params[MIX_PARAM1].value) / 10))));
  outputs[AUDIO_OUTPUT2].value = 5.0f * ((osc->sin() * ((10 - calculateMix(inputs[MIX_INPUT2].value, params[MIX_PARAM2].value)) / 10) + (osc->saw() * (calculateMix(inputs[MIX_INPUT2]. value, params[MIX_PARAM2].value) / 10))));
  outputs[AUDIO_OUTPUT3].value = 5.0f * ((osc->tri() * ((10 - calculateMix(inputs[MIX_INPUT3].value, params[MIX_PARAM3].value)) / 10) + (osc->saw() * (calculateMix(inputs[MIX_INPUT3]. value, params[MIX_PARAM3].value) / 10))));
}
