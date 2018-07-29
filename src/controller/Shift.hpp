#include <cstdint>

#include "../CharredDesert.hpp"

struct ShiftModule : Module {
  enum ParamIds { SWITCH, KNOB, NUM_PARAMS };
  enum InputIds { SHIFT, INPUT, NUM_INPUTS };
  enum OutputIds { OUTPUT, NUM_OUTPUTS };
  enum LightIds { NUM_LIGHTS };

  ShiftModule();
  void step() override;
};
