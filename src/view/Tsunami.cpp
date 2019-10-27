#include "../controller/Tsunami.hpp"

#include "components.hpp"

struct TsunamiWidget : ModuleWidget {
  TsunamiWidget(TsunamiModule *module);
};

TsunamiWidget::TsunamiWidget(TsunamiModule *module) {
  setModule(module);
  box.size = Vec(2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Tsunami.svg")));


  for (int i = 0; i < SHIFT_COUNT; i++) {
    addInput(createInput<CDPort>(Vec(10, 30 + (35 * i)), module,
                                   TsunamiModule::CV + i));

    addParam(createParam<LightKnobSmall>(Vec(57, 30 + (35 * i)), module, TsunamiModule::SHIFT + i));

    addParam(createParam<LightKnobSmall>(Vec(102, 30 + (35 * i)), module,
                                   TsunamiModule::LEVEL + i));

    addOutput(createOutput<CDPort>(Vec(145, 30 + (35 * i)), module,
                                   TsunamiModule::OUT + i));
  }

  addInput(createInput<CDPort>(Vec(10, 310), module, TsunamiModule::MASTER_IN));
  addParam(createParam<LightKnobSmall>(Vec(57, 310), module, TsunamiModule::MASTER_LEVEL));
  addOutput(createOutput<CDPort>(Vec(100, 310), module, TsunamiModule::POLY_OUT));
  addOutput(createOutput<CDPort>(Vec(145, 310), module, TsunamiModule::MASTER_OUT));
}

Model *modelTsunami = createModel<TsunamiModule, TsunamiWidget>("Tsunami");
