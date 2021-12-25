#include "CVSeq.hpp"

#define ADD_CV(a, b) clamp(a.value + b.value, 0.0f, 10.0f)

CVSeqModule::CVSeqModule() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  cv = new SynthDevKit::CV(1.7f);
  currentStep = 0;
  configParam(CVSeqModule::KNOB1, 0.0f, 10.0f, 0.0f, "Value");
  configParam(CVSeqModule::KNOB2, 0.0f, 10.0f, 0.0f, "Value");
  configParam(CVSeqModule::KNOB3, 0.0f, 10.0f, 0.0f, "Value");
  configParam(CVSeqModule::KNOB4, 0.0f, 10.0f, 0.0f, "Value");
}

void CVSeqModule::process(const ProcessArgs &args) {
  float cv_in = inputs[CV_INPUT].getVoltage();
  float current = 0.0f;

  cv->update(cv_in);

  if (cv->newTrigger()) {
    current = ADD_CV(inputs[currentStep], params[currentStep]);
    //  current = params[currentStep].getValue();
    outputs[CV_OUTPUT].setVoltage(current);
    for (int i = 0; i < 4; i++) {
      if (i == currentStep) {
        lights[i].value = 1.0;
      } else {
        lights[i].value = 0.0;
      }
    }
    currentStep++;

    if (currentStep == 4) {
      currentStep = 0;
    }
  }
}
