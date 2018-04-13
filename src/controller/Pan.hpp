#include <cstdint>

#include "../CharredDesert.hpp"
#include "../../deps/rack-components/jacks.hpp"

struct PanModule : Module {
  enum ParamIds { NUM_PARAMS };
  enum InputIds { AUDIO_INPUT, PAN_INPUT, NUM_INPUTS };
  enum OutputIds { AUDIO_OUTPUT1, AUDIO_OUTPUT2, NUM_OUTPUTS };
  enum LightIds { NUM_LIGHTS };

  PanModule();
  void step() override;
};
