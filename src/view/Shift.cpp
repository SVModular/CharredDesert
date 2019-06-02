#include "../controller/Shift.hpp"

#include "components.hpp"

struct ShiftWidget : ModuleWidget {
  ShiftWidget(ShiftModule *module);
};

ShiftWidget::ShiftWidget(ShiftModule *module) : ModuleWidget(module) {
  box.size = Vec(4 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(pluginInstance, "res/Shift.svg")));
    addChild(panel);
  }


  addInput(createPort<CDPort>(Vec(17.5, 35), PortWidget::INPUT, module,
                                ShiftModule::INPUT));
  addParam(createParam<CKSS>(Vec(22.5, 95), module, ShiftModule::SWITCH,
                                     0.0f, 1.0f, 0.0f));

  addParam(createParam<LightKnob>(
      Vec(28.5, 154.5), module, ShiftModule::KNOB, -5.0f, 5.0f, 0.0f));
  addInput(createPort<CDPort>(Vec(4, 160), PortWidget::INPUT, module,
                                ShiftModule::SHIFT));
  addOutput(createPort<CDPort>(Vec(17.5, 211), PortWidget::OUTPUT, module,
                                 ShiftModule::OUTPUT));
}

Model *modelShift = createModel<ShiftModule, ShiftWidget>("Shift");
