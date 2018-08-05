#include <cstdint>

#include "../CharredDesert.hpp"

#include "../../deps/SynthDevKit/src/CV.hpp"

#define CV_COUNT 2

struct CVModule : Module {
  enum ParamIds { KNOB, SWITCH = CV_COUNT, NUM_PARAMS = CV_COUNT * 2 };
  enum InputIds {  NUM_INPUTS };
  enum OutputIds { OUT, NUM_OUTPUTS = CV_COUNT };
  enum LightIds { OUT_LIGHT, NUM_LIGHTS = CV_COUNT };

  CVModule();

  void step() override;

  bool on[CV_COUNT];

  SynthDevKit::CV *cv[CV_COUNT];
};
