#include "../controller/MixerCV.hpp"

#include <cmath>

#include "../../deps/rack-components/screws.hpp"
#include "../../deps/rack-components/sliders.hpp"

#include "components.hpp"

struct MixerCVWidget : ModuleWidget {
  MixerCVWidget(MixerCVModule *module);
};

MixerCVWidget::MixerCVWidget(MixerCVModule *module) : ModuleWidget(module) {
  box.size = Vec(47 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(pluginInstance, "res/MixerCV.svg")));
    addChild(panel);
  }


  for (int i = 0; i < MIXER_CHANNELS; i++) {
    // input for each channel
    addInput(
        Port::create<CDPort>(Vec(10 + (45 * i), 20), Port::INPUT, module, MixerCVModule::INPUT + i));

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
                                           MixerCVModule::VOLUME_SLIDER + i, 0.0f,
                                           1.2f, 1.0f));

    // pan knob
    addParam(ParamWidget::create<LightKnob>(
        Vec(10 + (i * 45), 265), module, MixerCVModule::PAN_PARAM + i, 0.0f, 1.0f, 0.5f));

    // solo button
    addParam(ParamWidget::create<CDLEDBezel>(Vec(11 + (i * 45), 310), module,
                                           MixerCVModule::SOLO_PARAM + i, 0.0f,
                                           1.0f, 0.0f));
    addChild(ModuleLightWidget::create<CDButtonLight<GreenLight>>(
        Vec(13.2 + (i * 45), 312), module, MixerCVModule::SOLO_LIGHT + i));

    // mute button
    addParam(ParamWidget::create<CDLEDBezel>(Vec(11 + (i * 45), 343), module,
                                           MixerCVModule::MUTE_PARAM + i, 0.0f,
                                           1.0f, 0.0f));
    addChild(ModuleLightWidget::create<CDButtonLight<RedLight>>(
        Vec(13.2 + (i * 45), 345), module, MixerCVModule::MUTE_LIGHT + i));

  }

  // main outputs
  addOutput(Port::create<CDPort>(Vec(364, 20), Port::OUTPUT, module,
                                MixerCVModule::MAIN_L_OUT));
  addOutput(Port::create<CDPort>(Vec(392, 20), Port::OUTPUT, module,
                                 MixerCVModule::MAIN_R_OUT));

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
                                         MixerCVModule::VOLUME_L_MAIN, 0.0f,
                                         1.2f, 1.0f));
  addParam(ParamWidget::create<CDSlider>(Vec(393.35, 173), module,
                                        MixerCVModule::VOLUME_R_MAIN, 0.0f,
                                        1.2f, 1.0f));

  // mute
  addParam(ParamWidget::create<CDLEDBezel>(Vec(363, 287), module,
                                         MixerCVModule::MUTE_L_PARAM, 0.0f,
                                         1.0f, 0.0f));
  addChild(ModuleLightWidget::create<CDButtonLight<RedLight>>(
      Vec(365.2, 289), module, MixerCVModule::MUTE_L_MAIN));

  addParam(ParamWidget::create<CDLEDBezel>(Vec(393, 287), module,
                                         MixerCVModule::MUTE_R_PARAM, 0.0f,
                                         1.0f, 0.0f));
  addChild(ModuleLightWidget::create<CDButtonLight<RedLight>>(
      Vec(395.2, 289), module, MixerCVModule::MUTE_R_MAIN));


  for (int i = 0; i < MIXER_CHANNELS; i++) {
    // send output
    addOutput(Port::create<CDPort>(Vec(422 + (i * 30), 20), Port::OUTPUT, module,
                                  MixerCVModule::SEND + i));

    // recv input
    addInput(Port::create<CDPort>(Vec(422 + (i * 30), 66), Port::INPUT, module,
                                  MixerCVModule::RECV + i));

    // mix
    addParam(ParamWidget::create<LightKnobSmall>(Vec(425 + (i * 30), 112), module,
                                           MixerCVModule::MIX_PARAM + i, 0.0f,
                                           1.0f, 0.0f));

    addInput(Port::create<CDPort>(Vec(422 + (i * 30), 158), Port::INPUT, module,
                                   MixerCVModule::MIX_CV + i));

    // pan / volume cv
    addInput(Port::create<CDPort>(Vec(422 + (i * 30), 204), Port::INPUT, module,
                                   MixerCVModule::VOLUME_CV + i));
    addInput(Port::create<CDPort>(Vec(422 + (i * 30), 250), Port::INPUT, module,
                                  MixerCVModule::PAN_CV + i));

    // mute / solo cv
    addInput(Port::create<CDPort>(Vec(422 + (i * 30), 296), Port::INPUT, module,
                                  MixerCVModule::SOLO_CV + i));
    addInput(Port::create<CDPort>(Vec(422 + (i * 30), 342), Port::INPUT, module,
                                   MixerCVModule::MUTE_CV + i));

  }

  // main send l
  addOutput(Port::create<CDPort>(Vec(669.5, 20), Port::OUTPUT, module,
                                MixerCVModule::MAIN_L_SEND));

  // main recv l
  addInput(Port::create<CDPort>(Vec(669.5, 50), Port::INPUT, module,
                                MixerCVModule::MAIN_L_RECV));

  // mix l
  addParam(ParamWidget::create<LightKnob>(Vec(670, 85), module,
                                         MixerCVModule::MAIN_L_MIX, 0.0f,
                                         1.0f, 0.0f));
  // mix cv l
  addInput(Port::create<CDPort>(Vec(669.5, 122), Port::INPUT, module,
                                MixerCVModule::MAIN_MIX_L_CV));

  // mute l
  addInput(Port::create<CDPort>(Vec(669.5, 154), Port::INPUT, module,
                                MixerCVModule::MAIN_L_MUTE));

  // main send r
  addOutput(Port::create<CDPort>(Vec(669.5, 210), Port::OUTPUT, module,
                                 MixerCVModule::MAIN_R_SEND));

  // main recv r
  addInput(Port::create<CDPort>(Vec(669.5, 240), Port::INPUT, module,
                                 MixerCVModule::MAIN_R_RECV));

  // mix r
  addParam(ParamWidget::create<LightKnob>(Vec(670, 275), module,
                                         MixerCVModule::MAIN_R_MIX, 0.0f,
                                         1.0f, 0.0f));

  // main cv r
  addInput(Port::create<CDPort>(Vec(669.5, 312), Port::INPUT, module,
                                MixerCVModule::MAIN_MIX_R_CV));

  // main mute r
  addInput(Port::create<CDPort>(Vec(669.5, 344), Port::INPUT, module,
                                MixerCVModule::MAIN_R_MUTE));
}

Model *modelMixerCV = Model::create<MixerCVModule, MixerCVWidget>("Mixer CV");
