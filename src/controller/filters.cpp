#include <cstdint>

#include "filters.hpp"

void MoogFilter::clear() {
  f = 0;
  pc = 0;
  q = 0;
  bf0 = 0;
  bf1 = 0;
  bf2 = 0;
  bf3 = 0;
  bf4 = 0;
  t1 = 0;
  t2 = 0;
}

void MoogFilter::setCoefficients(float f_, float r_) {
  float frequency = f_ / (0.5 * sample_rate);
  float resonance = r_;

  if (frequency < 0)
    frequency = 0;
  if (frequency > 0.6)
    frequency = 0.6;

  q = 1.0f - frequency;
  pc = frequency + 0.8f * frequency * q;
  f = pc + pc - 1.0f;
  q = resonance * (1.0f + 0.5f * q * (1.0f - q + 5.6f * q * q));
}

void MoogFilter::process(float *input, float *output, int samples) {
  for (uint16_t i = 0; i < samples; i++) {
    float in = input[i];

    in -= q * bf4; // feedback
    t1 = bf1;
    bf1 = (in + bf0) * pc - bf1 * f;
    t2 = bf2;
    bf2 = (bf1 + t1) * pc - bf2 * f;
    t1 = bf3;
    bf3 = (bf2 + t2) * pc - bf3 * f;
    bf4 = (bf3 + t1) * pc - bf4 * f;
    bf4 = bf4 - bf4 * bf4 * bf4 * 0.166667f; // clipping
    bf0 = in;

    // Lowpass  output:  bf4
    // Highpass output:  in - bf4;
    // Bandpass output:  3.0f * (bf3 - bf4);
    output[i] = bf4;
  }
}
