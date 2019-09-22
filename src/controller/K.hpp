#include <cstdint>

#include "../CharredDesert.hpp"

#include "../model/Compressor.hpp"

struct KModule : Module {
  enum ParamIds { THRESHOLD, RATIO, ATTACK, RELEASE, NUM_PARAMS };
  enum InputIds {  IN, NUM_INPUTS };
  enum OutputIds { OUT, NUM_OUTPUTS };
  enum LightIds { ACTIVE, NUM_LIGHTS };

  KModule();

  void process(const ProcessArgs &args) override;
  Compressor compressor;
  float sampleRate = 0;
  float ratio = 0;
  float attackTime = 0;
  float releaseTime = 0;
  float threshold = 0;
};
