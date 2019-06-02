#include "../controller/Not.hpp"

#include "components.hpp"

struct NotWidget : ModuleWidget {
  NotWidget(NotModule *module);
};

NotWidget::NotWidget(NotModule *module) : ModuleWidget(module) {
  box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(pluginInstance, "res/Not.svg")));
    addChild(panel);
  }


  addInput(
      createPort<CDPort>(Vec(10, 35), PortWidget::INPUT, module, NotModule::INPUT));
  addParam(createParam<CKSS>(Vec(15, 95), module, NotModule::SWITCH,
                                     0.0, 1.0, 1.0));
  addOutput(createPort<CDPort>(Vec(10, 135), PortWidget::OUTPUT, module,
                                 NotModule::OUTPUT));
}

Model *modelNot = createModel<NotModule, NotWidget>("Not");
