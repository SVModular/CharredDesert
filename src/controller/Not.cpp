#include "Not.hpp"

NotModule::NotModule() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  configParam(NotModule::SWITCH, 0.0, 1.0, 1.0, "CV/Voct");
}

void NotModule::process(const ProcessArgs &args) {
  float in = inputs[INPUT].getVoltage();

  if (params[SWITCH].getValue() == 0) {
    outputs[OUTPUT].setVoltage(-in);
  } else {
    if (in >= 1.7f) {
      outputs[OUTPUT].setVoltage(0);
    } else {
      outputs[OUTPUT].setVoltage(1.7f);
    }
  }
}
