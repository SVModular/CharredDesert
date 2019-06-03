#include "Mixer.hpp"

MixerModule::MixerModule() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  for (int i = 0; i < MIXER_CHANNELS; i++) {
    channel_led_l[i] = 0.0f;
    channel_led_r[i] = 0.0f;
    mute[i] = false;
    solo[i] = false;

    mute_button[i] = new SynthDevKit::CV(0.5f);
    solo_button[i] = new SynthDevKit::CV(0.5f);

    configParam(MixerModule::VOLUME_SLIDER + i, 0.0f, 1.2f, 1.0f);
    configParam(MixerModule::PAN_PARAM + i, 0.0f, 1.0f, 0.5f);
    configParam(MixerModule::SOLO_PARAM + i, 0.0f, 1.0f, 0.0f);
    configParam(MixerModule::MUTE_PARAM + i, 0.0f, 1.0f, 0.0f);
  }

  configParam(MixerModule::VOLUME_L_MAIN, 0.0f, 1.2f, 1.0f);
  configParam(MixerModule::VOLUME_R_MAIN, 0.0f, 1.2f, 1.0f);
  configParam(MixerModule::MUTE_L_PARAM, 0.0f, 1.0f, 0.0f);
  configParam(MixerModule::MUTE_R_PARAM, 0.0f, 1.0f, 0.0f);

  master_led_l = 0.0f;
  master_led_r = 0.0f;
  master_mute_l = false;
  master_mute_r = false;

  mute_l = new SynthDevKit::CV(0.5f);
  mute_r = new SynthDevKit::CV(0.5f);
}

void MixerModule::process(const ProcessArgs &args) {
  bool has_solo = false;
  float output_l[MIXER_CHANNELS];
  float output_r[MIXER_CHANNELS];
  float master_l = 0.0f;
  float master_r = 0.0f;

  master_led_l = 0.0f;
  master_led_r = 0.0f;

  // check for solo buttons first and handle the button presses
  for (int i = 0; i < MIXER_CHANNELS; i++) {
    mute_button[i]->update(params[MUTE_PARAM + i].getValue());
    solo_button[i]->update(params[SOLO_PARAM + i].getValue());

    if (solo_button[i]->newTrigger()) {
      solo[i] = !solo[i];
    }

    if (mute_button[i]->newTrigger()) {
      mute[i] = !mute[i];
    }

    // if any are solo, there's a solo
    if (solo[i]) {
      has_solo = true;
    }
  }

  // iterate through the channels
  for (int i = 0; i < MIXER_CHANNELS; i++) {
    output_l[i] = 0.0f;
    output_r[i] = 0.0f;

    // if the input is not active, or the input is muted
    if (!inputs[INPUT + i].isConnected() || mute[i] || (has_solo && !solo[i])) {
      // set everything to 0
      output_l[i] = 0.0f;
      output_r[i] = 0.0f;
    } else {
      // do the math
      float input = inputs[INPUT + i].getVoltage();

      // get the volume slider value
      float volume = params[VOLUME_SLIDER + i].getValue();

      input *= volume;

      // figure out the left and right percentages
      float pan = params[PAN_PARAM + i].getValue();

      output_l[i] = output_r[i] = input;

      // determine the left/right mixes
      if (pan < 0.5f) {
        output_r[i] = (2.0f * pan) * output_r[i];
      }

      if (pan > 0.5f) {
        output_l[i] = (2.0f * (1.0f - pan)) * output_l[i];
      }

      // add the output to master
      // check if there is a solo, and it's not this one
      if (has_solo) {
        if (solo[i]) {
          master_l += output_l[i];
          master_r += output_r[i];
        }
      } else {
        master_l += output_l[i];
        master_r += output_r[i];
      }
    }

    lights[SOLO_LIGHT + i].value = solo[i] ? 1.0f : 0.0f;
    lights[MUTE_LIGHT + i].value = mute[i] ? 1.0f : 0.0f;

    // the led's
    channel_led_l[i] = fabsf(output_l[i]);
    channel_led_r[i] = fabsf(output_r[i]);
  }

  // check if muted
  mute_l->update(params[MUTE_L_PARAM].getValue());
  mute_r->update(params[MUTE_R_PARAM].getValue());

  if (mute_l->newTrigger()) {
    master_mute_l = !master_mute_l;
  }

  if (mute_r->newTrigger()) {
    master_mute_r = !master_mute_r;
  }

  if (master_mute_l) {
    master_l = 0.0f;
  } else {
    // apply the left volume
    float volume = params[VOLUME_L_MAIN].getValue();
    master_l = master_l * volume;
  }

  if (master_mute_r) {
    master_r = 0.0f;
  } else {
    // apply the left volume
    float volume = params[VOLUME_R_MAIN].getValue();
    master_r = master_r * volume;
  }

  lights[MUTE_L_MAIN].value = master_mute_l ? 1.0f : 0.0f;
  lights[MUTE_R_MAIN].value = master_mute_r ? 1.0f : 0.0f;

  // apply master volume to the led's
  master_led_l = fabsf(master_l);
  master_led_r = fabsf(master_r);

  // and to the output
  outputs[MAIN_L_OUT].setVoltage(master_l);
  outputs[MAIN_R_OUT].setVoltage(master_r);
}
