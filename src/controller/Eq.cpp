#include "Eq.hpp"

EqModule::EqModule() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  configParam(EqModule::FREQ_PARAM, 30.0f, 14000.0f, 7000.0f, "Frequency");
  configParam(EqModule::TYPE_PARAM, 0.0f, 6.0f, 0.0f, "Type");
  configParam(EqModule::Q_PARAM, 0.1f, 6.0f, 0.1f, "Q");
  sampleRate = APP->engine->getSampleRate();
  filter = new Biquad(bq_type_lowpass, frequency / sampleRate, q, 6);
  filter->calcBiquad();
}

float EqModule::paramValue (uint16_t param, uint16_t input, float low, float high) {
  float current = params[param].getValue();

  if (inputs[input].isConnected()) {
    // high - low, divided by one tenth input voltage, plus the current value
    current += ((inputs[input].getVoltage() / 10) * (high - low));
  }

  return clamp(current, low, high);
}

void EqModule::process(const ProcessArgs &args) {
  float audio_in = inputs[AUDIO_INPUT].getVoltage();
  float freq_param = paramValue(FREQ_PARAM, FREQ_CV_INPUT, 30, 14000);
  uint8_t filter_type = (uint8_t)params[TYPE_PARAM].getValue();
  float q_param = paramValue(Q_PARAM, Q_CV_INPUT, 0.1f, 6.0f);

  if (args.sampleRate != sampleRate || filter_type != filterType ||
      freq_param != frequency || q_param != q) {
    // reset the tracking variables
    frequency = freq_param;
    q = q_param;
    filterType = filter_type;
    sampleRate = args.sampleRate;

    filter->setType(filterType);
    filter->setQ((double)q);
    filter->setFc(frequency / sampleRate);
    filter->calcBiquad();
  }

  if (outputs[AUDIO_OUTPUT].isConnected()) {
    outputs[AUDIO_OUTPUT].setVoltage(5.0f * filter->process(audio_in / 5.0f));
  }
}
