#include "Pan.hpp"

PanModule::PanModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) { }

void PanModule::step() {
  float audio_in = inputs[AUDIO_INPUT].value;
  float pan_in = inputs[PAN_INPUT].value;

  // figure out the percentages to apply
  float apply1 = (clamp(pan_in, -5.0f, 5.0f) + 5.0f) * 10;
  float apply2 = 100.0f - apply1;

  outputs[AUDIO_OUTPUT1].value = ((audio_in * apply1) / 100.0f);
  outputs[AUDIO_OUTPUT2].value = ((audio_in * apply2) / 100.0f);
}
