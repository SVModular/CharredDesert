#include "../controller/Oscar2.hpp"

#include "../../deps/rack-components/display.hpp"
#include "components.hpp"

struct Oscar2Widget : ModuleWidget {
  Oscar2Widget(Oscar2Module *module);
};

Oscar2Widget::Oscar2Widget(Oscar2Module *module) {
  setModule(module);
  box.size = Vec(10 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Oscar2.svg")));

  // wave selection - left
  {
    WaveSelect *waveSelect = new WaveSelect();
    if (module) {
      waveSelect->value = &module->wave1;
    }
    waveSelect->box.pos = Vec(9.5, 33);
    waveSelect->box.size = Vec(10, 10);
    addChild(waveSelect);
  }

  // shape - left
  addInput(createInput<CDPort>(Vec(4, 85), module,
                                Oscar2Module::SHAPE_INPUT1));
  addParam(createParam<LightKnobSnap>(
      Vec(28.5, 79.5), module, Oscar2Module::SHAPE_PARAM1));

  // shift - left
  addInput(createInput<CDPort>(Vec(4, 135), module,
                                Oscar2Module::SHIFT_INPUT1));
  addParam(createParam<LightKnob>(
      Vec(28.5, 129.5), module, Oscar2Module::SHIFT_PARAM1));

  // octave - left
  addInput(createInput<CDPort>(Vec(4, 185), module,
                                Oscar2Module::OCTAVE_INPUT1));
  addParam(createParam<LightKnobSnap>(Vec(28.5, 179.5), module,
                                              Oscar2Module::OCTAVE_PARAM1));

  // fine - left
  addInput(createInput<CDPort>(Vec(4, 235), module,
                                Oscar2Module::FINE_INPUT1));
  addParam(createParam<LightKnob>(
      Vec(28.5, 229.5), module, Oscar2Module::FINE_PARAM1));

  // random - left
  addInput(createInput<CDPort>(Vec(4, 285), module,
                                Oscar2Module::RANDOM_INPUT1));
  addParam(createParam<LightKnob>(
      Vec(28.5, 279.5), module, Oscar2Module::RANDOM_PARAM1));

  // invert - left
  addParam(createParam<CKSS>(
      Vec(67, 108), module, Oscar2Module::INVERT_PARAM1));

  // wave selection - right
  {
    WaveSelect *waveSelect = new WaveSelect();
    if (module) {
      waveSelect->value = &module->wave2;
    }
    waveSelect->box.pos = Vec(55, 33);
    waveSelect->box.size = Vec(10, 10);
    addChild(waveSelect);
  }

  // shape - right
  addInput(createInput<CDPort>(Vec(94, 85), module,
                                Oscar2Module::SHAPE_INPUT2));
  addParam(createParam<LightKnobSnap>(
      Vec(118.5, 79.5), module, Oscar2Module::SHAPE_PARAM2));

  // shift - right
  addInput(createInput<CDPort>(Vec(94, 135), module,
                                Oscar2Module::SHIFT_INPUT2));
  addParam(createParam<LightKnob>(Vec(118.5, 129.5), module,
                                          Oscar2Module::SHIFT_PARAM2));

  // octave - right
  addInput(createInput<CDPort>(Vec(94, 185), module,
                                Oscar2Module::OCTAVE_INPUT2));
  addParam(createParam<LightKnobSnap>(Vec(118.5, 179.5), module,
                                              Oscar2Module::OCTAVE_PARAM2));

  // fine - right
  addInput(createInput<CDPort>(Vec(94, 235), module,
                                Oscar2Module::FINE_INPUT2));
  addParam(createParam<LightKnob>(
      Vec(118.5, 229.5), module, Oscar2Module::FINE_PARAM2));

  // random - right
  addInput(createInput<CDPort>(Vec(94, 285), module,
                                Oscar2Module::RANDOM_INPUT2));
  addParam(createParam<LightKnob>(Vec(118.5, 279.5), module,
                                          Oscar2Module::RANDOM_PARAM2));

  // invert - right
  addParam(createParam<CKSS>(
      Vec(67, 158), module, Oscar2Module::INVERT_PARAM2));

  // mix
  addInput(createInput<CDPort>(Vec(62.5, 227), module,
                                Oscar2Module::MIX_INPUT));
  addParam(createParam<LightKnob>(
      Vec(62.5, 252.5), module, Oscar2Module::MIX_PARAM));

  // v/oct
  addInput(createInput<CDPort>(Vec(22.5, 330), module,
                                Oscar2Module::FREQ_INPUT));

  // mix out
  addOutput(createOutput<CDPort>(Vec(102.5, 330), module,
                                 Oscar2Module::AUDIO_OUTPUT));
}

Model *modelOscar2 = createModel<Oscar2Module, Oscar2Widget>("Oscar2");
