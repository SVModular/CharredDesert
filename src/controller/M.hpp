#include <cstdint>

#include "../CharredDesert.hpp"

#include "../../deps/SynthDevKit/src/CV.hpp"

#define M_COUNT 2

struct MModule : Module {
  enum ParamIds { KNOB, NUM_PARAMS = M_COUNT };
  enum InputIds {  IN1, IN2 = M_COUNT, NUM_INPUTS = M_COUNT * 2 };
  enum OutputIds { OUT, NUM_OUTPUTS = M_COUNT };
  enum LightIds { NUM_LIGHTS };

  MModule();

  void step() override;
};
