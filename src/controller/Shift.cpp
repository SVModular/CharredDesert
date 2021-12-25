#include "Shift.hpp"

ShiftModule::ShiftModule() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  configParam(ShiftModule::SWITCH, 0.0f, 1.0f, 0.0f, "Natural/Clip");
  configParam(ShiftModule::KNOB, -5.0f, 5.0f, 0.0f, "Amount");
}

#define ADD_CV(a, b) (a.value + b.value)

void ShiftModule::process(const ProcessArgs &args) {
  float in = inputs[INPUT].getVoltage();

  float shift = ADD_CV(inputs[SHIFT], params[KNOB]);

  if (params[SWITCH].getValue()) {
    outputs[OUTPUT].setVoltage(clamp(in + shift, -5.0f, 5.0f));
  } else {
    outputs[OUTPUT].setVoltage(in + shift);
  }
}
