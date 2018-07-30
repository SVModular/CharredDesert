#include "Eq.hpp"

EqModule::EqModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
  sampleRate = engineGetSampleRate();
  filter = new Biquad(bq_type_lowpass, frequency / sampleRate, q, 6);
  filter->calcBiquad();
}

void EqModule::step() {
  float audio_in = inputs[AUDIO_INPUT].value;
  float freq_param = params[FREQ_PARAM].value;
  uint8_t filter_type = (uint8_t)params[TYPE_PARAM].value;
  float q_param = params[Q_PARAM].value;

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
