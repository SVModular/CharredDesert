#include "../controller/Mixer.hpp"

#include <cmath>

#include "../../deps/rack-components/screws.hpp"
#include "../../deps/rack-components/sliders.hpp"

#include "components.hpp"

struct MixerWidget : ModuleWidget {
  MixerWidget(MixerModule *module);
};

MixerWidget::MixerWidget(MixerModule *module) : ModuleWidget(module) {
  box.size = Vec(28 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/Mixer.svg")));
    addChild(panel);
  }


  for (int i = 0; i < MIXER_CHANNELS; i++) {
    // input for each channel
    addInput(
        Port::create<CDPort>(Vec(10 + (45 * i), 20), Port::INPUT, module, MixerModule::INPUT + i));

    // left volume LED
    {
      CDLEDSmallDisplay *led = new CDLEDSmallDisplay();
      led->value = &module->channel_led_l[i];
      led->box.pos = Vec(11 + (i * 45), 59);
      led->box.size = Vec(8, 80);
      addChild(led);
    }

    // right volume LED
    {
      CDLEDSmallDisplay *led = new CDLEDSmallDisplay();
      led->value = &module->channel_led_r[i];
      led->box.pos = Vec(25.5 + (i * 45), 59);
      led->box.size = Vec(8, 80);
      addChild(led);
    }

    // volume slider
    addParam(ParamWidget::create<CDSlider>(Vec(10.65 + (i * 45), 145), module,
                                           MixerModule::VOLUME_SLIDER + i, 0.0f,
                                           1.2f, 1.0f));

    // pan knob
    addParam(ParamWidget::create<LightKnob>(
        Vec(10 + (i * 45), 265), module, MixerModule::PAN_PARAM + i, 0.0f, 1.0f, 0.5f));

    // solo button
    addParam(ParamWidget::create<CDLEDBezel>(Vec(11 + (i * 45), 310), module,
                                           MixerModule::SOLO_PARAM + i, 0.0f,
                                           1.0f, 0.0f));
    addChild(ModuleLightWidget::create<CDButtonLight<GreenLight>>(
        Vec(13.2 + (i * 45), 312), module, MixerModule::SOLO_LIGHT + i));

    // mute button
    addParam(ParamWidget::create<CDLEDBezel>(Vec(11 + (i * 45), 343), module,
                                           MixerModule::MUTE_PARAM + i, 0.0f,
                                           1.0f, 0.0f));
    addChild(ModuleLightWidget::create<CDButtonLight<RedLight>>(
        Vec(13.2 + (i * 45), 345), module, MixerModule::MUTE_LIGHT + i));

  }

  // main outputs
  addOutput(Port::create<CDPort>(Vec(364, 20), Port::OUTPUT, module,
                                MixerModule::MAIN_L_OUT));
  addOutput(Port::create<CDPort>(Vec(392, 20), Port::OUTPUT, module,
                                 MixerModule::MAIN_R_OUT));

  // main LED
  // left master LED
  {
    CDLEDWideDisplay *led = new CDLEDWideDisplay();
    led->value = &module->master_led_l;
    led->box.pos = Vec(367, 59);
    led->box.size = Vec(16, 110);
    addChild(led);
  }

  // right master LED
  {
    CDLEDWideDisplay *led = new CDLEDWideDisplay();
    led->value = &module->master_led_r;
    led->box.pos = Vec(397, 59);
    led->box.size = Vec(16, 110);
    addChild(led);
  }

  // main volume
  addParam(ParamWidget::create<CDSlider>(Vec(363.35, 173), module,
                                         MixerModule::VOLUME_L_MAIN, 0.0f,
                                         1.2f, 1.0f));
  addParam(ParamWidget::create<CDSlider>(Vec(393.35, 173), module,
                                        MixerModule::VOLUME_R_MAIN, 0.0f,
                                        1.2f, 1.0f));

  // mute
  addParam(ParamWidget::create<CDLEDBezel>(Vec(363, 287), module,
                                         MixerModule::MUTE_L_PARAM, 0.0f,
                                         1.0f, 0.0f));
  addChild(ModuleLightWidget::create<CDButtonLight<RedLight>>(
      Vec(365.2, 289), module, MixerModule::MUTE_L_MAIN));

  addParam(ParamWidget::create<CDLEDBezel>(Vec(393, 287), module,
                                         MixerModule::MUTE_R_PARAM, 0.0f,
                                         1.0f, 0.0f));
  addChild(ModuleLightWidget::create<CDButtonLight<RedLight>>(
      Vec(395.2, 289), module, MixerModule::MUTE_R_MAIN));


}

Model *modelMixer = Model::create<MixerModule, MixerWidget>("CharredDesert", "Mixer",
                                                      "Mixer", MIXER_TAG);
