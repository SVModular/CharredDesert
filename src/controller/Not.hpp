#include <cstdint>

#include "../CharredDesert.hpp"
#include "../../deps/rack-components/jacks.hpp"

struct NotModule : Module {
  enum ParamIds { SWITCH, NUM_PARAMS };
  enum InputIds { INPUT, NUM_INPUTS };
  enum OutputIds { OUTPUT, NUM_OUTPUTS };
  enum LightIds { NUM_LIGHTS };

  NotModule();

  void step() override;
};
