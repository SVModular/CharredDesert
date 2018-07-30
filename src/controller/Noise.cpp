#include "Noise.hpp"

NoiseModule::NoiseModule()
    : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
  wn = new SynthDevKit::WhiteNoise(0);
  pn = new SynthDevKit::PinkNoise(0);
  cv = new SynthDevKit::CV(1.7f);
}

void NoiseModule::step() {
  float cv_in = inputs[CV_INPUT].value;

  cv->update(cv_in);

  if (cv->isHigh()) {
    if (params[NOISE_SWITCH].value) {
      outputs[AUDIO_OUTPUT].value = wn->stepValue();
    } else {
      outputs[AUDIO_OUTPUT].value = pn->stepValue();
    }

    lights[ON_LED].value = 1;
  } else {
    outputs[AUDIO_OUTPUT].value = 0;
    lights[ON_LED].value = 0;
  }
}
