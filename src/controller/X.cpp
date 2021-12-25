#include "X.hpp"

#include <cmath>

#define VALUE(a) (a.isConnected() ? a.getVoltage() : 0.0f)

XModule::XModule() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  for (int i = 0; i < X_COUNT; i++) {
    configParam(XModule::KNOB + i, 0.0f, 1.0f, 0.5f, "Mix");
  }
}

float XModule::paramValue (uint16_t param, uint16_t input, float low, float high) {
  float current = params[param].getValue();

  if (inputs[input].isConnected()) {
    // high - low, divided by one tenth input voltage, plus the current value
    current += ((inputs[input].getVoltage() / 10) * (high - low));
  }

  return clamp(current, low, high);
}


void XModule::process(const ProcessArgs &args) {
  for (int i = 0; i < X_COUNT; i++) {
    float mix = paramValue(KNOB + i, MIX + i, 0, 1);
    float x = inputs[IN + i].getVoltage();

    float out = (1 - mix) * VALUE(inputs[IN + i]) + mix * tanh(x);

    outputs[OUT + i].setVoltage(out);
  }
}
