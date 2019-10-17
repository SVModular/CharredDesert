#include <cstdint>

#include "../CharredDesert.hpp"

#include "../../deps/SynthDevKit/src/CV.hpp"

#define X_COUNT 2

struct XModule : Module {
  enum ParamIds { KNOB, NUM_PARAMS = X_COUNT };
  enum InputIds {  IN, MIX = X_COUNT, NUM_INPUTS = X_COUNT * 2 };
  enum OutputIds { OUT, NUM_OUTPUTS = X_COUNT };
  enum LightIds { NUM_LIGHTS };

  XModule();
  float paramValue (uint16_t, uint16_t, float, float);
  void process(const ProcessArgs &args) override;
};
