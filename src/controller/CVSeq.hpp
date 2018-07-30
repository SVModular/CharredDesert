#include <cstdint>

#include "../../deps/SynthDevKit/src/CV.hpp"
#include "../CharredDesert.hpp"

struct CVSeqModule : Module {
  enum ParamIds { KNOB1, KNOB2, KNOB3, KNOB4, NUM_PARAMS };
  enum InputIds {
    KNOB1_INPUT,
    KNOB2_INPUT,
    KNOB3_INPUT,
    KNOB4_INPUT,
    CV_INPUT,
    NUM_INPUTS
  };
  enum OutputIds { CV_OUTPUT, NUM_OUTPUTS };
  enum LightIds { LED1, LED2, LED3, LED4, NUM_LIGHTS };

  CVSeqModule();
  void step() override;

  SynthDevKit::CV *cv;
  uint8_t currentStep;
};
