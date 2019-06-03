#include <cstdint>

#include "../CharredDesert.hpp"

struct PanModule : Module {
  enum ParamIds { PAN_PARAM, NUM_PARAMS };
  enum InputIds { AUDIO_INPUT, PAN_INPUT, NUM_INPUTS };
  enum OutputIds { AUDIO_OUTPUT1, AUDIO_OUTPUT2, NUM_OUTPUTS };
  enum LightIds { NUM_LIGHTS };

  PanModule();
  void process(const ProcessArgs &args) override;
};
