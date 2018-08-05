#include <cstdint>

#include "../CharredDesert.hpp"
#include "../../deps/SynthDevKit/src/CV.hpp"

#define MIXER_CHANNELS 8

struct MixerCVModule : Module {
  enum ParamIds {
    VOLUME_SLIDER,
    PAN_PARAM = MIXER_CHANNELS,
    SOLO_PARAM = MIXER_CHANNELS * 2,
    MUTE_PARAM = MIXER_CHANNELS * 3,
    MIX_PARAM = MIXER_CHANNELS * 4,
    VOLUME_L_MAIN = MIXER_CHANNELS * 5,
    VOLUME_R_MAIN,
    MUTE_L_PARAM,
    MUTE_R_PARAM,
    MAIN_L_MIX,
    MAIN_R_MIX,
    NUM_PARAMS
  };
  enum InputIds {
    RECV,
    MIX_CV = MIXER_CHANNELS,
    MUTE_CV = MIXER_CHANNELS * 2,
    SOLO_CV = MIXER_CHANNELS * 3,
    PAN_CV = MIXER_CHANNELS * 4,
    VOLUME_CV = MIXER_CHANNELS * 5,
    INPUT = MIXER_CHANNELS * 6,
    MAIN_L_RECV = MIXER_CHANNELS * 7,
    MAIN_R_RECV,
    MAIN_L_MUTE,
    MAIN_R_MUTE,
    MAIN_MIX_L_CV,
    MAIN_MIX_R_CV,
    NUM_INPUTS
  };
  enum OutputIds {
    SEND,
    MAIN_L_OUT = MIXER_CHANNELS,
    MAIN_R_OUT,
    MAIN_L_SEND,
    MAIN_R_SEND,
    NUM_OUTPUTS
  };

  enum LightIds {
    SOLO_LIGHT,
    MUTE_LIGHT = MIXER_CHANNELS,
    MUTE_L_MAIN = MIXER_CHANNELS * 2,
    MUTE_R_MAIN,
    NUM_LIGHTS
  };

  MixerCVModule();
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
  SynthDevKit::CV *mute_l_param;
  SynthDevKit::CV *mute_r_param;

  SynthDevKit::CV *channel_mute[MIXER_CHANNELS];
  SynthDevKit::CV *channel_solo[MIXER_CHANNELS];

  json_t *toJson() override {
    json_t *rootJ = json_object();

    json_t *m = json_array();
    json_t *s = json_array();

    for (int i = 0; i < MIXER_CHANNELS; i++) {
      json_array_append(m, json_boolean(mute[i]));
      json_array_append(s, json_boolean(solo[i]));
    }

    json_object_set_new(rootJ, "mute", m);
    json_object_set_new(rootJ, "solo", s);
    json_object_set_new(rootJ, "mute_l", json_boolean(master_mute_l));
    json_object_set_new(rootJ, "mute_r", json_boolean(master_mute_r));

    return rootJ;
  }

  void fromJson(json_t *rootJ) override {
    json_t *m = json_object_get(rootJ, "mute");
    json_t *s = json_object_get(rootJ, "solo");

    for (int i = 0; i < MIXER_CHANNELS; i++) {
      if (m && json_is_array(m)) {
        json_t *m1 = json_array_get(m, i);
        if (m1) {
          mute[i] = json_boolean_value(m1);
        }
      }

      if (s && json_is_array(s)) {
        json_t *s1 = json_array_get(s, i);
        if (s1) {
          solo[i] = json_boolean_value(s1);
        }
      }
    }

    json_t *v = json_object_get(rootJ, "mute_l");
    if (v) {
      master_mute_l = json_boolean_value(v);
    } else {
      master_mute_l = false;
    }

    v = json_object_get(rootJ, "mute_r");
    if (v) {
      master_mute_r = json_boolean_value(v);
    } else {
      master_mute_l = false;
    }
  }
};
