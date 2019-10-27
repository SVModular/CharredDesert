#pragma once

#include <cstdint>

template <typename T> struct Delay {
  Delay(uint64_t length = 65536) {
    buffer = new T[length];
    delay = 0;
    inPoint = 0;
    outPoint = 0;
    this->length = length;

    clear();
  }

  ~Delay( ) {
    delete buffer;
  }

  void setDelay(uint64_t delay) {
    if (inPoint >= delay) {
      outPoint = inPoint - delay;
    } else {
      outPoint = length + inPoint - delay;
    }

    this->delay = delay;
  }

  void setMax(uint64_t delay) {
    if (delay > length) {
      delete buffer;
      buffer = new T[delay];

      for (uint64_t i = 0; i < delay; i++) {
        buffer[i] = 0;
      }
    }

    length = delay;
  }

  void clear( ) {
    for (uint64_t i = 0; i < length; i++) {
      buffer[i] = 0;
    }

    last = 0.0;
  }

  T nextOut( ) {
    return buffer[outPoint];
  }

  T step(T in) {
    buffer[inPoint] = in;
    inPoint++;

    if (inPoint == length) {
      inPoint = 0;
    }

    last = buffer[outPoint];
    outPoint++;

    if (outPoint == length) {
      outPoint = 0;
    }

    return last;
  }

  T *buffer;
  uint64_t length;
  uint64_t delay;
  uint64_t inPoint;
  uint64_t outPoint;
  T last;
};
