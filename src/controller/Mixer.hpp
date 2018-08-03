#include <cstdint>

#include "../CharredDesert.hpp"
#include "../../deps/SynthDevKit/src/CV.hpp"

#define MIXER_CHANNELS 8

struct MixerModule : Module {
  enum ParamIds {
    VOLUME_SLIDER,
    PAN_PARAM = MIXER_CHANNELS,
    SOLO_PARAM = MIXER_CHANNELS * 2,
    MUTE_PARAM = MIXER_CHANNELS * 3,
    VOLUME_L_MAIN = MIXER_CHANNELS * 4,
    VOLUME_R_MAIN,
    MUTE_L_PARAM,
    MUTE_R_PARAM,
    NUM_PARAMS
  };
  enum InputIds {
    INPUT,
    NUM_INPUTS = MIXER_CHANNELS
  };
  enum OutputIds {
    MAIN_L_OUT,
    MAIN_R_OUT,
    NUM_OUTPUTS
  };

  enum LightIds {
    SOLO_LIGHT,
    MUTE_LIGHT = MIXER_CHANNELS,
    MUTE_L_MAIN = MIXER_CHANNELS * 2,
    MUTE_R_MAIN,
    NUM_LIGHTS
  };

  MixerModule();
  void step() override;

  float channel_led_l[MIXER_CHANNELS];
  float channel_led_r[MIXER_CHANNELS];

  float master_led_l = 0.0f;
  float master_led_r = 0.0f;

  bool mute[MIXER_CHANNELS];
  bool master_mute_l;
  bool master_mute_r;

  bool solo[MIXER_CHANNELS];

  SynthDevKit::CV *solo_button[MIXER_CHANNELS];
  SynthDevKit::CV *mute_button[MIXER_CHANNELS];
  SynthDevKit::CV *mute_l;
  SynthDevKit::CV *mute_r;
};
