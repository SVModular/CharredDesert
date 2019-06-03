#include "../controller/M.hpp"

#include "components.hpp"

struct MWidget : ModuleWidget {
  MWidget(MModule *module);
};

MWidget::MWidget(MModule *module) {
  setModule(module);
  box.size = Vec(2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/M.svg")));


  for (int i = 0; i < M_COUNT; i++) {
    addInput(createInput<CDPort>(Vec(3, 30 + (190 * i)), module,
                                   MModule::IN1 + i));

    addInput(createInput<CDPort>(Vec(3, 65 + (190 * i)), module,
                                   MModule::IN2 + i));

    addParam(createParam<LightKnobSmall>(Vec(5, 102 + (190 * i)), module, MModule::KNOB + i));

    addOutput(createOutput<CDPort>(Vec(3, 140 + (190 * i)), module,
                                   MModule::OUT + i));
  }
}

Model *modelM = createModel<MModule, MWidget>("M");
