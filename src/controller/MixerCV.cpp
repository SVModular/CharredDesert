#include "MixerCV.hpp"

MixerCVModule::MixerCVModule()
    : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
  for (int i = 0; i < MIXER_CHANNELS; i++) {
    channel_led_l[i] = 0.0f;
    channel_led_r[i] = 0.0f;
    mute[i] = false;
    solo[i] = false;

    mute_button[i] = new SynthDevKit::CV(0.5f);
    solo_button[i] = new SynthDevKit::CV(0.5f);
    channel_solo[i] = new SynthDevKit::CV(1.7f);
    channel_mute[i] = new SynthDevKit::CV(1.7f);
  }

  master_led_l = 0.0f;
  master_led_r = 0.0f;
  master_mute_l = false;
  master_mute_r = false;

  mute_l = new SynthDevKit::CV(0.5f);
  mute_r = new SynthDevKit::CV(0.5f);
  mute_l_param = new SynthDevKit::CV(0.5f);
  mute_r_param = new SynthDevKit::CV(0.5f);
}

void MixerCVModule::step() {
  bool has_solo = false;
  float output_l[MIXER_CHANNELS];
  float output_r[MIXER_CHANNELS];
  float master_l = 0.0f;
  float master_r = 0.0f;

  master_led_l = 0.0f;
  master_led_r = 0.0f;

  // check for solo buttons first and handle the button presses and cv
  for (int i = 0; i < MIXER_CHANNELS; i++) {
    channel_solo[i]->update(inputs[SOLO_CV + i].value);
    channel_mute[i]->update(inputs[MUTE_CV + i].value);

    mute_button[i]->update(params[MUTE_PARAM + i].value);
    solo_button[i]->update(params[SOLO_PARAM + i].value);

    // buttons first
    if (solo_button[i]->newTrigger()) {
      solo[i] = !solo[i];
      lights[SOLO_LIGHT + i].value = solo[i] ? 1.0f : 0.0f;
    }

    if (mute_button[i]->newTrigger()) {
      mute[i] = !mute[i];
      lights[MUTE_LIGHT + i].value = mute[i] ? 1.0f : 0.0f;
    }

    // then cv
    if (channel_solo[i]->newTrigger()) {
      solo[i] = !solo[i];
      lights[SOLO_LIGHT + i].value = solo[i] ? 1.0f : 0.0f;
    }

    if (channel_mute[i]->newTrigger()) {
      mute[i] = !mute[i];
      lights[MUTE_LIGHT + i].value = mute[i] ? 1.0f : 0.0f;
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
    if (mute[i] || (has_solo && !solo[i])) {
      // set everything to 0
      output_l[i] = 0.0f;
      output_r[i] = 0.0f;
    } else {
      // get the input
      float input = (inputs[INPUT + i].active ? inputs[INPUT + i].value : 0.0f);

      // send the input if there's something listening
      if (outputs[SEND + i].active) {
        outputs[SEND + i].value = input;
      }

      // if there in recv, process it
      if (inputs[RECV + i].active) {
        // get the mix
        float mix = clamp((inputs[MIX_CV + i].active ? inputs[MIX_CV + i].value / 10 : 0.0f) + params[MIX_PARAM + i].value, 0.0f, 1.0f);

        // calculate the new "input"
        input = ((1 - mix) * input) + (mix * inputs[RECV + i].value);
      }

      // get the volume slider value
      float volume = params[VOLUME_SLIDER + i].value;

      // add any cv value
      volume = clamp((inputs[VOLUME_CV + i].active ? inputs[VOLUME_CV + i].value / 10 : 0.0f) + volume, 0.0f, 1.2f);

      input *= volume;

      // figure out the left and right percentages
      float pan = params[PAN_PARAM + i].value;

      // add any cv value
      pan = clamp((inputs[PAN_CV + i].active ? inputs[PAN_CV + i].value : 0) / 10 + pan, 0.0f, 1.0f);

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

    // the led's
    channel_led_l[i] = fabsf(output_l[i]);
    channel_led_r[i] = fabsf(output_r[i]);
  }

  // check if muted
  mute_l_param->update(params[MUTE_L_PARAM].value);

  if (mute_l_param->newTrigger()) {
    master_mute_l = !master_mute_l;
    lights[MUTE_L_MAIN].value = master_mute_l ? 1.0f : 0.0f;
  }

  if (inputs[MAIN_L_MUTE].active) {
    mute_l->update(inputs[MAIN_L_MUTE].value);

    if (mute_l->newTrigger()) {
      master_mute_l = !master_mute_l;
      lights[MUTE_L_MAIN].value = master_mute_l ? 1.0f : 0.0f;
    }
  }

  if (master_mute_l) {
    master_l = 0.0f;
  } else {
    // if there's something to send to, send
    if (outputs[MAIN_L_SEND].active) {
      outputs[MAIN_L_SEND].value = master_l;
    }

    // if there is something to receive, calculate the new value
    if (inputs[MAIN_L_RECV].active) {
      // get the mix
      float mix = clamp((inputs[MAIN_MIX_L_CV].active ? inputs[MAIN_MIX_L_CV].value : 0.0f) + params[MAIN_L_MIX].value, 0.0f, 1.0f);

      // calculate the new "input"
      master_l = ((1 - mix) * master_l) + (mix * inputs[MAIN_L_RECV].value);
    }

    // apply the left volume
    float volume = params[VOLUME_L_MAIN].value;
    master_l = master_l * volume;
  }

  mute_r_param->update(params[MUTE_R_PARAM].value);

  if (mute_r_param->newTrigger()) {
    master_mute_r = !master_mute_r;
    lights[MUTE_R_MAIN].value = master_mute_r ? 1.0f : 0.0f;
  }

  if (inputs[MAIN_R_MUTE].active) {
    mute_r->update(inputs[MAIN_R_MUTE].value);

    if (mute_r->newTrigger()) {
      master_mute_r = !master_mute_r;
      lights[MUTE_R_MAIN].value = master_mute_r ? 1.0f : 0.0f;
    }
  }

  if (master_mute_r) {
    master_r = 0.0f;
  } else {
    // if there's something to send to, send
    if (outputs[MAIN_R_SEND].active) {
      outputs[MAIN_R_SEND].value = master_l;
    }

    // if there is something to receive, calculate the new value
    if (inputs[MAIN_R_RECV].active) {
      // get the mix
      float mix = clamp((inputs[MAIN_MIX_R_CV].active ? inputs[MAIN_MIX_R_CV].value : 0.0f) + params[MAIN_R_MIX].value, 0.0f, 1.0f);

      // calculate the new "input"
      master_r = ((1 - mix) * master_r) + (mix * inputs[MAIN_R_RECV].value);
    }

    // apply the left volume
    float volume = params[VOLUME_R_MAIN].value;
    master_r = master_r * volume;
  }


  // apply master volume to the led's
  master_led_l = fabsf(master_l);
  master_led_r = fabsf(master_r);

  // and to the output
  outputs[MAIN_L_OUT].value = master_l;
  outputs[MAIN_R_OUT].value = master_r;
}
