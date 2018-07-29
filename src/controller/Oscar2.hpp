#include <cstdint>

#include "../CharredDesert.hpp"

#include "../../deps/SynthDevKit/src/CV.hpp"

#include "../LFO.hpp"

struct Oscar2Module : Module {
  enum ParamIds {
    SHAPE_PARAM1,
    SHAPE_PARAM2,
    SHIFT_PARAM1,
    SHIFT_PARAM2,
    OCTAVE_PARAM1,
    OCTAVE_PARAM2,
    FINE_PARAM1,
    FINE_PARAM2,
    RANDOM_PARAM1,
    RANDOM_PARAM2,
    MIX_PARAM,
    INVERT_PARAM1,
    INVERT_PARAM2,
    NUM_PARAMS
  };
  enum InputIds {
    SHAPE_INPUT1,
    SHAPE_INPUT2,
    SHIFT_INPUT1,
    SHIFT_INPUT2,
    OCTAVE_INPUT1,
    OCTAVE_INPUT2,
    FINE_INPUT1,
    FINE_INPUT2,
    RANDOM_INPUT1,
    RANDOM_INPUT2,
    MIX_INPUT,
    FREQ_INPUT,
    NUM_INPUTS
  };
  enum OutputIds {
    AUDIO_OUTPUT,
    NUM_OUTPUTS
  };
  enum LightIds { NUM_LIGHTS };

  Oscar2Module();

  void step() override;

  float shift1 = 0.0f;
  float shift2 = 0.0f;
  uint8_t wave1 = 0;
  uint8_t wave2 = 0;
  LowFrequencyOscillator *osc1;
  LowFrequencyOscillator *osc2;
  float value = 0.0f;
};
