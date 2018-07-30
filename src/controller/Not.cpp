#include "Not.hpp"

NotModule::NotModule()
    : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
}

void NotModule::step() {
  float in = inputs[INPUT].value;

  if (params[SWITCH].value == 0) {
    outputs[OUTPUT].value = -in;
  } else {
    if (in >= 1.7f) {
      outputs[OUTPUT].value = 0;
    } else {
      outputs[OUTPUT].value = 1.7f;
    }
  }
}
