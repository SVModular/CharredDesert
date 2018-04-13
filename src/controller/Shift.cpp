#include "Shift.hpp"

ShiftModule::ShiftModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) { }

void ShiftModule::step() {
  float in = inputs[INPUT].value;

  float shift = params[KNOB].value;

  if (params[SWITCH].value) {
    outputs[OUTPUT].value = clamp(in + shift, -5.0f, 5.0f);
  } else {
    outputs[OUTPUT].value = in + shift;
  }
}
