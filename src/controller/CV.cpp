#include "CV.hpp"
#include <cstdio>

CVModule::CVModule() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  for (int i = 0; i < CV_COUNT; i++) {
    on[i] = false;
    cv[i] = new SynthDevKit::CV(0.5f);
    configParam(CVModule::SWITCH + i, 0.0f, 1.0f, 0.0f, "On/Off");
    configParam(CVModule::KNOB + i, 0.0f, 10.0f, 0.0f, "Value");
  }
}

void CVModule::process(const ProcessArgs &args) {
  for (int i = 0; i < CV_COUNT; i++) {
    cv[i]->update(params[SWITCH + i].getValue());
    if (cv[i]->newTrigger()) {
      on[i] = !on[i];
    }

    if (on[i]) {
      lights[OUT_LIGHT + i].value = 1.0f;
      outputs[OUT + i].setVoltage(params[KNOB + i].getValue());
    } else {
      lights[OUT_LIGHT + i].value = 0.0f;
      outputs[OUT + i].setVoltage(0.0f);
    }
  }
}
