#include "Pan.hpp"

PanModule::PanModule() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  configParam(PanModule::PAN_PARAM, -5.0f, 5.0f, 0.0f, "Pan");
}

#define ADD_CV(a, b) clamp(a.value + b.value, -5.0f, 5.0f)

void PanModule::process(const ProcessArgs &args) {
  float audio_in = inputs[AUDIO_INPUT].getVoltage();
  float pan_in = ADD_CV(inputs[PAN_INPUT], params[PAN_PARAM]);

  // figure out the percentages to apply
  float apply1 = (clamp(pan_in, -5.0f, 5.0f) + 5.0f) * 10;
  float apply2 = 100.0f - apply1;

  outputs[AUDIO_OUTPUT1].setVoltage(((audio_in * apply1) / 100.0f));
  outputs[AUDIO_OUTPUT2].setVoltage(((audio_in * apply2) / 100.0f));
}
