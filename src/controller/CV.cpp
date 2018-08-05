#include "CV.hpp"

CVModule::CVModule()
    : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
  for (int i = 0; i < CV_COUNT; i++) {
    on[i] = false;
    cv[i] = new SynthDevKit::CV(0.5f);
  }
}

void CVModule::step() {
  for (int i = 0; i < CV_COUNT; i++) {
    cv[i]->update(params[SWITCH + i].value);
    if (cv[i]->newTrigger()) {
      on[i] = !on[i];
    }

    if (on[i]) {
      lights[OUT_LIGHT + i].value = 1.0f;
      outputs[OUT + i].value = params[KNOB + i].value;
    } else {
      lights[OUT_LIGHT + i].value = 0.0f;
      outputs[OUT + i].value = 0.0f;
    }
  }
}
