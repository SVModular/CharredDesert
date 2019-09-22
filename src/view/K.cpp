#include "../controller/K.hpp"

#include "components.hpp"

struct KWidget : ModuleWidget {
  KWidget(KModule *module);
};

KWidget::KWidget(KModule *module) {
  setModule(module);
  box.size = Vec(2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/K.svg")));


  addParam(createParam<LightKnobSmall>(Vec(5, 47), module, KModule::THRESHOLD));
  addParam(createParam<LightKnobSmall>(Vec(5, 87), module, KModule::RATIO));
  addParam(createParam<LightKnobSmall>(Vec(5, 127), module, KModule::ATTACK));
  addParam(createParam<LightKnobSmall>(Vec(5, 167), module, KModule::RELEASE));

  addInput(createInput<CDPort>(Vec(3, 210), module,
                                 KModule::IN));


  addOutput(createOutput<CDPort>(Vec(3, 250), module,
                                 KModule::OUT));

  addChild(createLight<MediumLight<RedLight>>(
      Vec(10, 297), module, KModule::ACTIVE));

}

Model *modelK = createModel<KModule, KWidget>("K");
