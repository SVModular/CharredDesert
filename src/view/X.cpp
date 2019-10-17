#include "../controller/X.hpp"

#include "components.hpp"

struct XWidget : ModuleWidget {
  XWidget(XModule *module);
};

XWidget::XWidget(XModule *module) {
  setModule(module);
  box.size = Vec(2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/X.svg")));


  for (int i = 0; i < X_COUNT; i++) {
    addInput(createInput<CDPort>(Vec(3, 30 + (190 * i)), module,
                                   XModule::IN + i));

    addOutput(createOutput<CDPort>(Vec(3, 140 + (190 * i)), module,
                                   XModule::OUT + i));

    addParam(createParam<LightKnobSmall>(Vec(5, 102 + (190 * i)), module, XModule::KNOB + i));

    addInput(createInput<CDPort>(Vec(3, 65 + (190 * i)), module,
                                   XModule::MIX + i));
  }
}

Model *modelX = createModel<XModule, XWidget>("X");
