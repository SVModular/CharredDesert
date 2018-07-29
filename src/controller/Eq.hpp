#include <cstdint>

#include "../CharredDesert.hpp"
#include "Biquad.h"

struct EqModule : Module {
  enum ParamIds { FREQ_PARAM, TYPE_PARAM, Q_PARAM, NUM_PARAMS };
  enum InputIds { AUDIO_INPUT, NUM_INPUTS };
  enum OutputIds { AUDIO_OUTPUT, NUM_OUTPUTS };
  enum LightIds { NUM_LIGHTS };

  EqModule();
  void step() override;

  float frequency = 0.0f;
  float sampleRate = 0.0f;
  uint8_t filterType = 0;
  float q = 0.0f;
  Biquad *filter = new Biquad();
};
