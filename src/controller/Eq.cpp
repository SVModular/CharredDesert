#include "Eq.hpp"

EqModule::EqModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
  sampleRate = engineGetSampleRate();
  filter = new Biquad(bq_type_lowpass, frequency / sampleRate, q, 6);
  filter->calcBiquad();
}

float EqModule::paramValue (uint16_t param, uint16_t input, float low, float high) {
  float current = params[param].value;

  if (inputs[input].active) {
    // high - low, divided by one tenth input voltage, plus the current value
    current += ((inputs[input].value / 10) * (high - low));
  }

  return clamp(current, low, high);
}

void EqModule::step() {
  float audio_in = inputs[AUDIO_INPUT].value;
  float freq_param = paramValue(FREQ_PARAM, FREQ_CV_INPUT, 30, 14000);
  uint8_t filter_type = (uint8_t)params[TYPE_PARAM].value;
  float q_param = paramValue(Q_PARAM, Q_CV_INPUT, 0.1f, 6.0f);

  if (engineGetSampleRate() != sampleRate || filter_type != filterType ||
      freq_param != frequency || q_param != q) {
    // reset the tracking variables
    frequency = freq_param;
    q = q_param;
    filterType = filter_type;
    sampleRate = engineGetSampleRate();

    filter->setType(filterType);
    filter->setQ((double)q);
    filter->setFc(frequency / sampleRate);
    filter->calcBiquad();
  }

  if (outputs[AUDIO_OUTPUT].active) {
    outputs[AUDIO_OUTPUT].value = 5.0f * filter->process(audio_in / 5.0f);
  }
}
