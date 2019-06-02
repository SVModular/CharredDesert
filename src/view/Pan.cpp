#include "../controller/Pan.hpp"

#include "components.hpp"

struct PanWidget : ModuleWidget {
  PanWidget(PanModule *module);
};

PanWidget::PanWidget(PanModule *module) : ModuleWidget(module) {
  box.size = Vec(4 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(pluginInstance, "res/Pan.svg")));
    addChild(panel);
  }


  addInput(createPort<CDPort>(Vec(17.5, 35), PortWidget::INPUT, module,
                                PanModule::AUDIO_INPUT));
  addParam(createParam<LightKnob>(
      Vec(28.5, 79.5), module, PanModule::PAN_PARAM, -5.0f, 5.0f, 0.0f));
  addInput(createPort<CDPort>(Vec(4, 85), PortWidget::INPUT, module,
                                PanModule::PAN_INPUT));
  addOutput(createPort<CDPort>(Vec(17.5, 135), PortWidget::OUTPUT, module,
                                 PanModule::AUDIO_OUTPUT1));
  addOutput(createPort<CDPort>(Vec(17.5, 185), PortWidget::OUTPUT, module,
                                 PanModule::AUDIO_OUTPUT2));
}

Model *modelPan = createModel<PanModule, PanWidget>("Pan");
