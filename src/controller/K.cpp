#include "K.hpp"

#define VALUE(a) (a.isConnected() ? a.getVoltage() : 0.0f)

KModule::KModule() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  configParam(RATIO, 1.0f, 10.0f, 5.0f);
  configParam(THRESHOLD, 1.0f, 30.0f, 10.0f);
  configParam(ATTACK, 1.0, 100.0, 10.0);
  configParam(RELEASE, 1.0, 100.0, 10.0);
}

void KModule::process(const ProcessArgs &args) {
  float r = params[RATIO].getValue();
  float t = params[THRESHOLD].getValue();
  float at = params[ATTACK].getValue();
  float rt = params[RELEASE].getValue();

  if (sampleRate != args.sampleRate || ratio != r || threshold != t || attackTime != at || releaseTime != rt) {
    sampleRate = args.sampleRate;
    ratio = r;
    threshold = t;
    attackTime = at;
    releaseTime = rt;

    compressor.setCoefficients(attackTime, releaseTime, threshold, ratio, sampleRate);
  }

  float in = inputs[IN].getVoltage();
  float out = compressor.process(in);
  lights[ACTIVE].value = (in == out) ? 0.0f : 1.0f;

  outputs[OUT].setVoltage(out);
}
