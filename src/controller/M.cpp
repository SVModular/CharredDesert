#include "M.hpp"

#define VALUE(a) (a.active ? a.value : 0.0f)
MModule::MModule()
    : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
}

void MModule::step() {
  for (int i = 0; i < M_COUNT; i++) {
    float mix = params[KNOB + i].value;

    float out = (1 - mix) * VALUE(inputs[IN1 + i]) + mix * VALUE(inputs[IN2 + i]);

    outputs[OUT + i].value = out;
  }
}
