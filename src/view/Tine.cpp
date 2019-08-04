#include "../controller/Tine.hpp"

#include "components.hpp"

struct TineWidget : ModuleWidget {
  TineWidget(TineModule *module);
};

TineWidget::TineWidget(TineModule *module) {
  setModule(module);
  box.size = Vec(4 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Tine.svg")));


  addInput(createInput<CDPort>(Vec(4, 35), module,
                                TineModule::AUDIO_IN));
  addInput(createInput<CDPort>(Vec(32, 35), module,
                                 TineModule::MODIFIER_IN));

  addParam(createParam<CKSS>(Vec(23, 85), module, TineModule::POLARITY));

  addInput(createInput<CDPort>(Vec(4, 135), module,
                                TineModule::SPLIT_CV));
  addParam(createParam<LightKnob>(
      Vec(28.5, 129.5), module, TineModule::SPLIT));

  addInput(createInput<CDPort>(Vec(4, 185), module,
                                TineModule::LOWER_ATT_CV));
  addParam(createParam<LightKnob>(
      Vec(28.5, 179.5), module, TineModule::LOWER_ATT));

  addInput(createInput<CDPort>(Vec(4, 235), module,
                                TineModule::UPPER_ATT_CV));
  addParam(createParam<LightKnob>(
      Vec(28.5, 229.5), module, TineModule::UPPER_ATT));

  addOutput(createOutput<CDPort>(Vec(4, 285), module,
                                TineModule::LOWER_OUT));
  addOutput(createOutput<CDPort>(Vec(32, 285), module,
                                 TineModule::UPPER_OUT));

  addChild(createLight<MediumLight<GreenLight>>(
      Vec(12, 177), module, TineModule::LOWER_LIGHT));
  addChild(createLight<MediumLight<GreenLight>>(
      Vec(12, 227), module, TineModule::UPPER_LIGHT));
}

Model *modelTine = createModel<TineModule, TineWidget>("Tine");
