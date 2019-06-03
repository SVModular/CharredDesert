#include "Oscar2.hpp"

static float calculateFrequency(float voltage) {
  return 261.626f * powf(2.0f, voltage);
}

static float calculateMix(float input, float param) {
  return clamp((input + param), 0.0f, 10.0f);
}

static float calculateShift(float frequency, float percent) {
  return (frequency * (percent / 100));
}

static float valueForWave(LowFrequencyOscillator *osc, uint8_t wave) {
  if (wave == 0) {
    return osc->sin();
  } else if (wave == 1) {
    return osc->tri();
  } else if (wave == 2) {
    return osc->saw();
  } else if (wave == 3) {
    return osc->sqr();
  } else {
    return 0.0f;
  }
}

Oscar2Module::Oscar2Module() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  osc1 = new LowFrequencyOscillator;
  osc2 = new LowFrequencyOscillator;

  configParam(Oscar2Module::SHAPE_PARAM1, 0.0f, 3.0f, 0.0f);
  configParam(Oscar2Module::SHIFT_PARAM1, 0.0f, 10.0f, 0.0f);
  configParam(Oscar2Module::OCTAVE_PARAM1, -4.0f, 4.0f, 0.0f);
  configParam(Oscar2Module::FINE_PARAM1, -1.0f, 1.0f, 0.0f);
  configParam(Oscar2Module::RANDOM_PARAM1, 0.0f, 5.0f, 0.0f);
  configParam(Oscar2Module::INVERT_PARAM1, 0.0f, 1.0f, 1.0f);
  configParam(Oscar2Module::SHAPE_PARAM2, 0.0f, 3.0f, 0.0f);
  configParam(Oscar2Module::SHIFT_PARAM2, 0.0f, 10.0f, 0.0f);
  configParam(Oscar2Module::OCTAVE_PARAM2, -4.0f, 4.0f, 0.0f);
  configParam(Oscar2Module::FINE_PARAM2, -1.0f, 1.0f, 0.0f);
  configParam(Oscar2Module::RANDOM_PARAM2, 0.0f, 5.0f, 0.0f);
  configParam(Oscar2Module::INVERT_PARAM2, 0.0f, 1.0f, 1.0f);
}

void Oscar2Module::process(const ProcessArgs &args) {
  float freq = inputs[FREQ_INPUT].getVoltage();

  osc1->setInvert(params[INVERT_PARAM1].getValue() ? false : true);
  osc2->setInvert(params[INVERT_PARAM2].getValue() ? false : true);

  float w1 = clamp(params[SHAPE_PARAM1].getValue() + inputs[SHAPE_INPUT1].getVoltage(),
                   0.0f, 3.0f);
  wave1 = (uint8_t)w1;

  float s1 = clamp(params[SHIFT_PARAM1].getValue() + inputs[SHIFT_INPUT1].getVoltage(),
                   0.0f, 10.0f) *
             10;

  if (s1 != shift1) {
    osc1->setShift(calculateShift(calculateFrequency(freq), s1));
    osc1->hardReset();
    osc2->hardReset();
    shift1 = s1;
  }

  float octave1 = clamp(params[OCTAVE_PARAM1].getValue() + inputs[OCTAVE_INPUT1].getVoltage(), -5.0f, 5.0f);
  float fine1 = params[FINE_PARAM1].getValue() + (inputs[FINE_INPUT1].getVoltage() / 2);

  float freq1 = clamp(freq + octave1 + fine1, -5.0f, 5.0f);
  osc1->setFrequency(calculateFrequency(freq1));

  float rand1 =
      clamp(params[RANDOM_PARAM1].getValue() + (inputs[RANDOM_INPUT1].getVoltage() / 2),
            0.0f, 5.0f);
  osc1->setRandom(rand1);

  float w2 = clamp(params[SHAPE_PARAM2].getValue() + inputs[SHAPE_INPUT2].getVoltage(),
                   0.0f, 3.0f);
  wave2 = (uint8_t)w2;

  float s2 = clamp(params[SHIFT_PARAM2].getValue() + inputs[SHIFT_INPUT2].getVoltage(),
                   0.0f, 10.0f) *
             10;

  if (s2 != shift2) {
    osc2->setShift(calculateShift(calculateFrequency(freq), s1));
    osc2->hardReset();
    osc1->hardReset();
    shift2 = s2;
  }

  float octave2 = params[OCTAVE_PARAM2].getValue() + inputs[OCTAVE_INPUT2].getVoltage();
  float fine2 = params[FINE_PARAM2].getValue() + (inputs[FINE_INPUT2].getVoltage() / 2);

  float freq2 = clamp(freq + octave2 + fine2, -5.0f, 5.0f);
  osc2->setFrequency(calculateFrequency(freq2));

  float rand2 =
      clamp(params[RANDOM_PARAM2].getValue() + (inputs[RANDOM_INPUT2].getVoltage() / 2),
            0.0f, 5.0f);
  osc2->setRandom(rand2);

  osc1->step(args.sampleTime);
  osc2->step(args.sampleTime);

  float left = valueForWave(osc1, wave1);
  float right = valueForWave(osc2, wave2);

  outputs[AUDIO_OUTPUT].value =
      5.0f * ((left * ((10 - calculateMix(inputs[MIX_INPUT].getVoltage(),
                                          params[MIX_PARAM].getValue())) /
                       10) +
               (right * (calculateMix(inputs[MIX_INPUT].getVoltage(),
                                      params[MIX_PARAM].getValue()) /
                         10))));
}
