#include <cstdint>

#include "../CharredDesert.hpp"

#include "../../deps/SynthDevKit/src/CV.hpp"
#include "../../deps/SynthDevKit/src/PinkNoise.hpp"
#include "../../deps/SynthDevKit/src/WhiteNoise.hpp"
#include "../../deps/rack-components/jacks.hpp"

struct NoiseModule : Module {
  enum ParamIds { NOISE_SWITCH, NUM_PARAMS };
  enum InputIds { CV_INPUT, NUM_INPUTS };
  enum OutputIds { AUDIO_OUTPUT, NUM_OUTPUTS };
  enum LightIds { ON_LED, NUM_LIGHTS };

  NoiseModule();

  void step() override;

  SynthDevKit::WhiteNoise *wn;
  SynthDevKit::PinkNoise *pn;
  SynthDevKit::CV *cv;
};
