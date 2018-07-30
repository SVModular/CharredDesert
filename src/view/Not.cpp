#include "../controller/Not.hpp"

#include "../../deps/rack-components/screws.hpp"
#include "components.hpp"

struct NotWidget : ModuleWidget {
  NotWidget(NotModule *module);
};

NotWidget::NotWidget(NotModule *module) : ModuleWidget(module) {
  box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/Not.svg")));
    addChild(panel);
  }

  addChild(Widget::create<JLHHexScrew>(Vec(16, 1)));
  addChild(Widget::create<JLHHexScrew>(Vec(16, 366)));

  addInput(
      Port::create<CDPort>(Vec(10, 35), Port::INPUT, module, NotModule::INPUT));
  addParam(ParamWidget::create<CKSS>(Vec(15, 95), module, NotModule::SWITCH,
                                     0.0, 1.0, 1.0));
  addOutput(Port::create<CDPort>(Vec(10, 135), Port::OUTPUT, module,
                                 NotModule::OUTPUT));
}

Model *modelNot = Model::create<NotModule, NotWidget>("CharredDesert", "Not",
                                                      "Not", LOGIC_TAG);
