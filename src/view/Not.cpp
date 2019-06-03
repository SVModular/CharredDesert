#include "../controller/Not.hpp"

#include "components.hpp"

struct NotWidget : ModuleWidget {
  NotWidget(NotModule *module);
};

NotWidget::NotWidget(NotModule *module) {
  setModule(module);
  box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Not.svg")));


  addInput(
      createInput<CDPort>(Vec(10, 35), module, NotModule::INPUT));
  addParam(createParam<CKSS>(Vec(15, 95), module, NotModule::SWITCH));
  addOutput(createOutput<CDPort>(Vec(10, 135), module,
                                 NotModule::OUTPUT));
}

Model *modelNot = createModel<NotModule, NotWidget>("Not");
