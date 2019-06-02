#include "../controller/MixerCV.hpp"

#include <cmath>


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
        createPort<CDPort>(Vec(10 + (45 * i), 20), PortWidget::INPUT, module, MixerCVModule::INPUT + i));

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
                                           MixerCVModule::VOLUME_SLIDER + i, 0.0f,
                                           1.2f, 1.0f));

    // pan knob
    addParam(createParam<LightKnob>(
        Vec(10 + (i * 45), 265), module, MixerCVModule::PAN_PARAM + i, 0.0f, 1.0f, 0.5f));

    // solo button
    addParam(createParam<CDLEDBezel>(Vec(11 + (i * 45), 310), module,
                                           MixerCVModule::SOLO_PARAM + i, 0.0f,
                                           1.0f, 0.0f));
    addChild(createLight<CDButtonLight<GreenLight>>(
        Vec(13.2 + (i * 45), 312), module, MixerCVModule::SOLO_LIGHT + i));

    // mute button
    addParam(createParam<CDLEDBezel>(Vec(11 + (i * 45), 343), module,
                                           MixerCVModule::MUTE_PARAM + i, 0.0f,
                                           1.0f, 0.0f));
    addChild(createLight<CDButtonLight<RedLight>>(
        Vec(13.2 + (i * 45), 345), module, MixerCVModule::MUTE_LIGHT + i));

  }

  // main outputs
  addOutput(createPort<CDPort>(Vec(364, 20), PortWidget::OUTPUT, module,
                                MixerCVModule::MAIN_L_OUT));
  addOutput(createPort<CDPort>(Vec(392, 20), PortWidget::OUTPUT, module,
                                 MixerCVModule::MAIN_R_OUT));

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
                                         MixerCVModule::VOLUME_L_MAIN, 0.0f,
                                         1.2f, 1.0f));
  addParam(createParam<CDSlider>(Vec(393.35, 173), module,
                                        MixerCVModule::VOLUME_R_MAIN, 0.0f,
                                        1.2f, 1.0f));

  // mute
  addParam(createParam<CDLEDBezel>(Vec(363, 287), module,
                                         MixerCVModule::MUTE_L_PARAM, 0.0f,
                                         1.0f, 0.0f));
  addChild(createLight<CDButtonLight<RedLight>>(
      Vec(365.2, 289), module, MixerCVModule::MUTE_L_MAIN));

  addParam(createParam<CDLEDBezel>(Vec(393, 287), module,
                                         MixerCVModule::MUTE_R_PARAM, 0.0f,
                                         1.0f, 0.0f));
  addChild(createLight<CDButtonLight<RedLight>>(
      Vec(395.2, 289), module, MixerCVModule::MUTE_R_MAIN));


  for (int i = 0; i < MIXER_CHANNELS; i++) {
    // send output
    addOutput(createPort<CDPort>(Vec(422 + (i * 30), 20), PortWidget::OUTPUT, module,
                                  MixerCVModule::SEND + i));

    // recv input
    addInput(createPort<CDPort>(Vec(422 + (i * 30), 66), PortWidget::INPUT, module,
                                  MixerCVModule::RECV + i));

    // mix
    addParam(createParam<LightKnobSmall>(Vec(425 + (i * 30), 112), module,
                                           MixerCVModule::MIX_PARAM + i, 0.0f,
                                           1.0f, 0.0f));

    addInput(createPort<CDPort>(Vec(422 + (i * 30), 158), PortWidget::INPUT, module,
                                   MixerCVModule::MIX_CV + i));

    // pan / volume cv
    addInput(createPort<CDPort>(Vec(422 + (i * 30), 204), PortWidget::INPUT, module,
                                   MixerCVModule::VOLUME_CV + i));
    addInput(createPort<CDPort>(Vec(422 + (i * 30), 250), PortWidget::INPUT, module,
                                  MixerCVModule::PAN_CV + i));

    // mute / solo cv
    addInput(createPort<CDPort>(Vec(422 + (i * 30), 296), PortWidget::INPUT, module,
                                  MixerCVModule::SOLO_CV + i));
    addInput(createPort<CDPort>(Vec(422 + (i * 30), 342), PortWidget::INPUT, module,
                                   MixerCVModule::MUTE_CV + i));

  }

  // main send l
  addOutput(createPort<CDPort>(Vec(669.5, 20), PortWidget::OUTPUT, module,
                                MixerCVModule::MAIN_L_SEND));

  // main recv l
  addInput(createPort<CDPort>(Vec(669.5, 50), PortWidget::INPUT, module,
                                MixerCVModule::MAIN_L_RECV));

  // mix l
  addParam(createParam<LightKnob>(Vec(670, 85), module,
                                         MixerCVModule::MAIN_L_MIX, 0.0f,
                                         1.0f, 0.0f));
  // mix cv l
  addInput(createPort<CDPort>(Vec(669.5, 122), PortWidget::INPUT, module,
                                MixerCVModule::MAIN_MIX_L_CV));

  // mute l
  addInput(createPort<CDPort>(Vec(669.5, 154), PortWidget::INPUT, module,
                                MixerCVModule::MAIN_L_MUTE));

  // main send r
  addOutput(createPort<CDPort>(Vec(669.5, 210), PortWidget::OUTPUT, module,
                                 MixerCVModule::MAIN_R_SEND));

  // main recv r
  addInput(createPort<CDPort>(Vec(669.5, 240), PortWidget::INPUT, module,
                                 MixerCVModule::MAIN_R_RECV));

  // mix r
  addParam(createParam<LightKnob>(Vec(670, 275), module,
                                         MixerCVModule::MAIN_R_MIX, 0.0f,
                                         1.0f, 0.0f));

  // main cv r
  addInput(createPort<CDPort>(Vec(669.5, 312), PortWidget::INPUT, module,
                                MixerCVModule::MAIN_MIX_R_CV));

  // main mute r
  addInput(createPort<CDPort>(Vec(669.5, 344), PortWidget::INPUT, module,
                                MixerCVModule::MAIN_R_MUTE));
}

Model *modelMixerCV = createModel<MixerCVModule, MixerCVWidget>("Mixer CV");
