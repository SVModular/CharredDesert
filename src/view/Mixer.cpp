#include "../controller/Mixer.hpp"

#include <cmath>


#include "components.hpp"

struct MixerWidget : ModuleWidget {
  MixerWidget(MixerModule *module);
};

MixerWidget::MixerWidget(MixerModule *module) : ModuleWidget(module) {
  box.size = Vec(28 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(pluginInstance, "res/Mixer.svg")));
    addChild(panel);
  }


  for (int i = 0; i < MIXER_CHANNELS; i++) {
    // input for each channel
    addInput(
        createPort<CDPort>(Vec(10 + (45 * i), 20), PortWidget::INPUT, module, MixerModule::INPUT + i));

    // left volume LED
    {
      CDLEDSmallDisplay *led = new CDLEDSmallDisplay();
      if (module) {
        led->value = &module->channel_led_l[i];
      }
      led->box.pos = Vec(11 + (i * 45), 59);
      led->box.size = Vec(8, 80);
      addChild(led);
    }

    // right volume LED
    {
      CDLEDSmallDisplay *led = new CDLEDSmallDisplay();
      if (module) {
        led->value = &module->channel_led_r[i];
      }
      led->box.pos = Vec(25.5 + (i * 45), 59);
      led->box.size = Vec(8, 80);
      addChild(led);
    }

    // volume slider
    addParam(createParam<CDSlider>(Vec(10.65 + (i * 45), 145), module,
                                           MixerModule::VOLUME_SLIDER + i, 0.0f,
                                           1.2f, 1.0f));

    // pan knob
    addParam(createParam<LightKnob>(
        Vec(10 + (i * 45), 265), module, MixerModule::PAN_PARAM + i, 0.0f, 1.0f, 0.5f));

    // solo button
    addParam(createParam<CDLEDBezel>(Vec(11 + (i * 45), 310), module,
                                           MixerModule::SOLO_PARAM + i, 0.0f,
                                           1.0f, 0.0f));
    addChild(createLight<CDButtonLight<GreenLight>>(
        Vec(13.2 + (i * 45), 312), module, MixerModule::SOLO_LIGHT + i));

    // mute button
    addParam(createParam<CDLEDBezel>(Vec(11 + (i * 45), 343), module,
                                           MixerModule::MUTE_PARAM + i, 0.0f,
                                           1.0f, 0.0f));
    addChild(createLight<CDButtonLight<RedLight>>(
        Vec(13.2 + (i * 45), 345), module, MixerModule::MUTE_LIGHT + i));

  }

  // main outputs
  addOutput(createPort<CDPort>(Vec(364, 20), PortWidget::OUTPUT, module,
                                MixerModule::MAIN_L_OUT));
  addOutput(createPort<CDPort>(Vec(392, 20), PortWidget::OUTPUT, module,
                                 MixerModule::MAIN_R_OUT));

  // main LED
  // left master LED
  {
    CDLEDWideDisplay *led = new CDLEDWideDisplay();
    if (module) {
      led->value = &module->master_led_l;
    }
    led->box.pos = Vec(367, 59);
    led->box.size = Vec(16, 110);
    addChild(led);
  }

  // right master LED
  {
    CDLEDWideDisplay *led = new CDLEDWideDisplay();
    if (module) {
      led->value = &module->master_led_r;
    }
    led->box.pos = Vec(397, 59);
    led->box.size = Vec(16, 110);
    addChild(led);
  }

  // main volume
  addParam(createParam<CDSlider>(Vec(363.35, 173), module,
                                         MixerModule::VOLUME_L_MAIN, 0.0f,
                                         1.2f, 1.0f));
  addParam(createParam<CDSlider>(Vec(393.35, 173), module,
                                        MixerModule::VOLUME_R_MAIN, 0.0f,
                                        1.2f, 1.0f));

  // mute
  addParam(createParam<CDLEDBezel>(Vec(363, 287), module,
                                         MixerModule::MUTE_L_PARAM, 0.0f,
                                         1.0f, 0.0f));
  addChild(createLight<CDButtonLight<RedLight>>(
      Vec(365.2, 289), module, MixerModule::MUTE_L_MAIN));

  addParam(createParam<CDLEDBezel>(Vec(393, 287), module,
                                         MixerModule::MUTE_R_PARAM, 0.0f,
                                         1.0f, 0.0f));
  addChild(createLight<CDButtonLight<RedLight>>(
      Vec(395.2, 289), module, MixerModule::MUTE_R_MAIN));


}

Model *modelMixer = createModel<MixerModule, MixerWidget>("Mixer");
