#include "../controller/Oscar2.hpp"

#include "../../deps/rack-components/display.hpp"
#include "components.hpp"

struct Oscar2Widget : ModuleWidget {
  Oscar2Widget(Oscar2Module *module);
};

Oscar2Widget::Oscar2Widget(Oscar2Module *module) : ModuleWidget(module) {
  box.size = Vec(10 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(pluginInstance, "res/Oscar2.svg")));
    addChild(panel);
  }

  /*
    {
      ValueDisplay *vd = new ValueDisplay();
      vd->value = &module->value;
      vd->box.pos = Vec(35, 142);
      vd->box.size = Vec(10, 10);
      addChild(vd);
    }
  */
  // wave selection - left
  {
    WaveSelect *waveSelect = new WaveSelect();
    waveSelect->value = &module->wave1;
    waveSelect->box.pos = Vec(9.5, 33);
    waveSelect->box.size = Vec(10, 10);
    addChild(waveSelect);
  }

  // shape - left
  addInput(createPort<CDPort>(Vec(4, 85), PortWidget::INPUT, module,
                                Oscar2Module::SHAPE_INPUT1));
  addParam(createParam<LightKnobSnap>(
      Vec(28.5, 79.5), module, Oscar2Module::SHAPE_PARAM1, 0.0f, 3.0f, 0.0f));

  // shift - left
  addInput(createPort<CDPort>(Vec(4, 135), PortWidget::INPUT, module,
                                Oscar2Module::SHIFT_INPUT1));
  addParam(createParam<LightKnob>(
      Vec(28.5, 129.5), module, Oscar2Module::SHIFT_PARAM1, 0.0f, 10.0f, 0.0f));

  // octave - left
  addInput(createPort<CDPort>(Vec(4, 185), PortWidget::INPUT, module,
                                Oscar2Module::OCTAVE_INPUT1));
  addParam(createParam<LightKnobSnap>(Vec(28.5, 179.5), module,
                                              Oscar2Module::OCTAVE_PARAM1,
                                              -4.0f, 4.0f, 0.0f));

  // fine - left
  addInput(createPort<CDPort>(Vec(4, 235), PortWidget::INPUT, module,
                                Oscar2Module::FINE_INPUT1));
  addParam(createParam<LightKnob>(
      Vec(28.5, 229.5), module, Oscar2Module::FINE_PARAM1, -1.0f, 1.0f, 0.0f));

  // random - left
  addInput(createPort<CDPort>(Vec(4, 285), PortWidget::INPUT, module,
                                Oscar2Module::RANDOM_INPUT1));
  addParam(createParam<LightKnob>(
      Vec(28.5, 279.5), module, Oscar2Module::RANDOM_PARAM1, 0.0f, 5.0f, 0.0f));

  // invert - left
  addParam(createParam<CKSS>(
      Vec(67, 108), module, Oscar2Module::INVERT_PARAM1, 0.0f, 1.0f, 1.0f));

  // wave selection - right
  {
    WaveSelect *waveSelect = new WaveSelect();
    waveSelect->value = &module->wave2;
    waveSelect->box.pos = Vec(55, 33);
    waveSelect->box.size = Vec(10, 10);
    addChild(waveSelect);
  }

  // shape - right
  addInput(createPort<CDPort>(Vec(94, 85), PortWidget::INPUT, module,
                                Oscar2Module::SHAPE_INPUT2));
  addParam(createParam<LightKnobSnap>(
      Vec(118.5, 79.5), module, Oscar2Module::SHAPE_PARAM2, 0.0f, 3.0f, 0.0f));

  // shift - right
  addInput(createPort<CDPort>(Vec(94, 135), PortWidget::INPUT, module,
                                Oscar2Module::SHIFT_INPUT2));
  addParam(createParam<LightKnob>(Vec(118.5, 129.5), module,
                                          Oscar2Module::SHIFT_PARAM2, 0.0f,
                                          10.0f, 0.0f));

  // octave - right
  addInput(createPort<CDPort>(Vec(94, 185), PortWidget::INPUT, module,
                                Oscar2Module::OCTAVE_INPUT2));
  addParam(createParam<LightKnobSnap>(Vec(118.5, 179.5), module,
                                              Oscar2Module::OCTAVE_PARAM2,
                                              -4.0f, 4.0f, 0.0f));

  // fine - right
  addInput(createPort<CDPort>(Vec(94, 235), PortWidget::INPUT, module,
                                Oscar2Module::FINE_INPUT2));
  addParam(createParam<LightKnob>(
      Vec(118.5, 229.5), module, Oscar2Module::FINE_PARAM2, -1.0f, 1.0f, 0.0f));

  // random - right
  addInput(createPort<CDPort>(Vec(94, 285), PortWidget::INPUT, module,
                                Oscar2Module::RANDOM_INPUT2));
  addParam(createParam<LightKnob>(Vec(118.5, 279.5), module,
                                          Oscar2Module::RANDOM_PARAM2, 0.0f,
                                          5.0f, 0.0f));

  // invert - right
  addParam(createParam<CKSS>(
      Vec(67, 158), module, Oscar2Module::INVERT_PARAM2, 0.0f, 1.0f, 1.0f));

  // mix
  addInput(createPort<CDPort>(Vec(62.5, 227), PortWidget::INPUT, module,
                                Oscar2Module::MIX_INPUT));
  addParam(createParam<LightKnob>(
      Vec(62.5, 252.5), module, Oscar2Module::MIX_PARAM, 0.0f, 10.0f, 5.0f));

  // v/oct
  addInput(createPort<CDPort>(Vec(22.5, 330), PortWidget::INPUT, module,
                                Oscar2Module::FREQ_INPUT));

  // mix out
  addOutput(createPort<CDPort>(Vec(102.5, 330), PortWidget::OUTPUT, module,
                                 Oscar2Module::AUDIO_OUTPUT));
}

Model *modelOscar2 = createModel<Oscar2Module, Oscar2Widget>("Oscar^2");
