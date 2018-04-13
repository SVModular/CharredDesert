#include <cstdint>

#include "../CharredDesert.hpp"
#include "../../deps/rack-components/jacks.hpp"
#include "../../deps/rack-components/knobs.hpp"

struct ShiftModule : Module {
  enum ParamIds { SWITCH, KNOB, NUM_PARAMS };
  enum InputIds { INPUT, NUM_INPUTS };
  enum OutputIds { OUTPUT, NUM_OUTPUTS };
  enum LightIds { NUM_LIGHTS };

  ShiftModule();
  void step() override;
};
