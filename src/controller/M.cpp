#include "M.hpp"

#define VALUE(a) (a.isConnected() ? a.getVoltage() : 0.0f)

MModule::MModule() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  for (int i = 0; i < M_COUNT; i++) {
    configParam(MModule::KNOB + i, 0.0f, 1.0f, 0.5f, "Volume");
  }
}

void MModule::process(const ProcessArgs &args) {
  for (int i = 0; i < M_COUNT; i++) {
    float mix = params[KNOB + i].getValue();

    float out = (1 - mix) * VALUE(inputs[IN1 + i]) + mix * VALUE(inputs[IN2 + i]);

    outputs[OUT + i].setVoltage(out);
  }
}
