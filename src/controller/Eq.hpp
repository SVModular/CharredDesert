#include <cstdint>

#include "../CharredDesert.hpp"
#include "Biquad.h"

struct EqModule : Module {
  enum ParamIds { FREQ_PARAM, TYPE_PARAM, Q_PARAM, NUM_PARAMS };
  enum InputIds { AUDIO_INPUT, FREQ_CV_INPUT, Q_CV_INPUT, NUM_INPUTS };
  enum OutputIds { AUDIO_OUTPUT, NUM_OUTPUTS };
  enum LightIds { NUM_LIGHTS };

  EqModule();
  void step() override;
  float paramValue (uint16_t, uint16_t, float, float);
  float frequency = 7000.0f;
  float sampleRate;
  uint8_t filterType = 0;
  float q = 0.1f;
  Biquad *filter;
};
