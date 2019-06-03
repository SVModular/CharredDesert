#include <cstdint>

#include "../../deps/SynthDevKit/src/CV.hpp"
#include "../../deps/SynthDevKit/src/DTMF.hpp"
#include "../CharredDesert.hpp"

struct DTMFModule : Module {
  enum ParamIds { NUM_PARAMS };
  enum InputIds { VOCT_INPUT, CV_INPUT, NUM_INPUTS };
  enum OutputIds { AUDIO_OUTPUT, NUM_OUTPUTS };
  enum LightIds { ON_LED, NUM_LIGHTS };

  DTMFModule();

  void process(const ProcessArgs &args) override;

  char getTone(float);

  SynthDevKit::CV *cv;
  SynthDevKit::DTMF *dtmf;
  float notes[16] = {0,    0.08, 0.17, 0.25, 0.33, 0.42, 0.5,  0.58,
                     0.67, 0.75, 0.83, 0.92, 1.0,  1.08, 1.17, 1.25};
  char tones[16] = {'1', '2', '3', 'A', '4', '5', '6', 'B',
                    '7', '8', '9', 'C', '*', '0', '#', 'D'};
};
