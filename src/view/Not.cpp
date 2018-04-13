#include "../controller/Not.hpp"

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

  addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(Widget::create<ScrewSilver>(
      Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

  addInput(Port::create<RCJackSmallRed>(Vec(10, 45), Port::INPUT, module, NotModule::INPUT));
  addParam(ParamWidget::create<CKSS>(Vec(15, 112), module, NotModule::SWITCH,
                             0.0, 1.0, 1.0));
  addOutput(
      Port::create<RCJackSmallRed>(Vec(10, 165), Port::OUTPUT, module, NotModule::OUTPUT));
}

Model *modelNot = Model::create<NotModule, NotWidget>("CharredDesert", "Not", "Not", LOGIC_TAG);
