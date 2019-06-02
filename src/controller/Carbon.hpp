#include "../CharredDesert.hpp"
#include "filters.hpp"

struct CarbonModule : Module {
  enum ParamIds { FREQ_PARAM, REZ_PARAM, NUM_PARAMS };
  enum InputIds { FREQ_INPUT, REZ_INPUT, AUDIO_INPUT, NUM_INPUTS };
  enum OutputIds { AUDIO_OUTPUT, NUM_OUTPUTS };
  enum LightIds { NUM_LIGHTS };

  CarbonModule();
  void step() override;
  MoogFilter filter;
  float frequency = 0.0f;
};
