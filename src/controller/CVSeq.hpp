#include <cstdint>

#include "../CharredDesert.hpp"
#include "../../deps/SynthDevKit/src/CV.hpp"
#include "../../deps/rack-components/knobs.hpp"
#include "../../deps/rack-components/jacks.hpp"

struct CVSeqModule : Module {
  enum ParamIds { KNOB1, KNOB2, KNOB3, KNOB4, NUM_PARAMS };
  enum InputIds { CV_INPUT, NUM_INPUTS };
  enum OutputIds { CV_OUTPUT, NUM_OUTPUTS };
  enum LightIds { LED1, LED2, LED3, LED4, NUM_LIGHTS };

  CVSeqModule();
  void step() override;

  SynthDevKit::CV *cv;
  uint8_t currentStep;
};
