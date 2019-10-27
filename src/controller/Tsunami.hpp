#include <cstdint>

#include "../CharredDesert.hpp"

#include "../model/Delay.hpp"

#define SHIFT_COUNT 8

struct TsunamiModule : Module {
  enum ParamIds { LEVEL, SHIFT = LEVEL + SHIFT_COUNT, MASTER_LEVEL = SHIFT + SHIFT_COUNT, NUM_PARAMS };
  enum InputIds {  CV, IN = CV + SHIFT_COUNT, MASTER_IN = IN + SHIFT_COUNT, NUM_INPUTS };
  enum OutputIds { OUT, POLY_OUT = OUT + SHIFT_COUNT, MASTER_OUT, NUM_OUTPUTS };
  enum LightIds { NUM_LIGHTS };

  TsunamiModule();

  void process(const ProcessArgs &args) override;
  float paramValue (uint16_t, uint16_t, float, float);

  float sampleRate;

  Delay<float> delay[SHIFT_COUNT];
};
