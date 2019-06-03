#include "DTMF.hpp"

DTMFModule::DTMFModule() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  cv = new SynthDevKit::CV(1.7f);
  dtmf = new SynthDevKit::DTMF(44100);
}

char DTMFModule::getTone(float current) {
  for (int i = 0; i < 16; i++) {
    if ((notes[i] - 0.02) <= current && (notes[i] + 0.02) >= current) {
      return tones[i];
    }
  }

  return ' ';
}

void DTMFModule::process(const ProcessArgs &args) {
  float cv_in = inputs[CV_INPUT].getVoltage();
  float voct_in = inputs[VOCT_INPUT].getVoltage();

  cv->update(cv_in);

  if (cv->newTrigger()) {
    dtmf->reset();
  }

  if (cv->isHigh()) {
    char tone = getTone(voct_in);
    dtmf->setTone(tone);

    outputs[AUDIO_OUTPUT].setVoltage(dtmf->stepValue());

    if (outputs[AUDIO_OUTPUT].value == 0) {
      lights[ON_LED].value = 0;
    } else {
      lights[ON_LED].value = 1;
    }
  } else {
    outputs[AUDIO_OUTPUT].setVoltage(0);
    lights[ON_LED].value = 0;
  }
}
