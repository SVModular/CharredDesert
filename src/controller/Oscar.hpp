#include <cstdint>

#include "../CharredDesert.hpp"

#include "../../deps/SynthDevKit/src/CV.hpp"
#include "../../deps/rack-components/jacks.hpp"
#include "../../deps/rack-components/knobs.hpp"

#include "../LFO.hpp"

struct OscarModule : Module {
  enum ParamIds {
    MIX_PARAM1,
    MIX_PARAM2,
    MIX_PARAM3,
    MIX_PARAM4,
    MIX_PARAM5,
    MIX_PARAM6,
    NUM_PARAMS
  };
  enum InputIds {
    MIX_INPUT1,
    MIX_INPUT2,
    MIX_INPUT3,
    MIX_INPUT4,
    MIX_INPUT5,
    MIX_INPUT6,
    FREQ_INPUT,
    NUM_INPUTS
  };
  enum OutputIds {
    AUDIO_OUTPUT1,
    AUDIO_OUTPUT2,
    AUDIO_OUTPUT3,
    AUDIO_OUTPUT4,
    AUDIO_OUTPUT5,
    AUDIO_OUTPUT6,
    NUM_OUTPUTS
  };
  enum LightIds { NUM_LIGHTS };

  OscarModule();

  LowFrequencyOscillator *osc;
  void step() override;
};
