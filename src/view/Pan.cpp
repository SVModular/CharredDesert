#include "../controller/Pan.hpp"

struct PanWidget : ModuleWidget {
  PanWidget(PanModule *module);
};

PanWidget::PanWidget(PanModule *module) : ModuleWidget(module) {
  box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/Pan.svg")));
    addChild(panel);
  }

  addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(Widget::create<ScrewSilver>(
      Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

  addInput(Port::create<RCJackSmallRed>(Vec(10, 45), Port::INPUT, module, PanModule::AUDIO_INPUT));
  addInput(Port::create<RCJackSmallRed>(Vec(10, 100), Port::INPUT, module, PanModule::PAN_INPUT));
  addOutput(Port::create<RCJackSmallRed>(Vec(10, 165), Port::OUTPUT, module, PanModule::AUDIO_OUTPUT1));
  addOutput(Port::create<RCJackSmallRed>(Vec(10, 230), Port::OUTPUT, module, PanModule::AUDIO_OUTPUT2));
}

Model *modelPan = Model::create<PanModule, PanWidget>("CharredDesert", "Pan", "Pan", PANNING_TAG);
