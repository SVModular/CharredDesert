#include "../controller/Shift.hpp"

#include "../../deps/rack-components/screws.hpp"
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


  addInput(Port::create<CDPort>(Vec(17.5, 35), Port::INPUT, module,
                                ShiftModule::INPUT));
  addParam(ParamWidget::create<CKSS>(Vec(22.5, 95), module, ShiftModule::SWITCH,
                                     0.0f, 1.0f, 0.0f));

  addParam(ParamWidget::create<LightKnob>(
      Vec(28.5, 154.5), module, ShiftModule::KNOB, -5.0f, 5.0f, 0.0f));
  addInput(Port::create<CDPort>(Vec(4, 160), Port::INPUT, module,
                                ShiftModule::SHIFT));
  addOutput(Port::create<CDPort>(Vec(17.5, 211), Port::OUTPUT, module,
                                 ShiftModule::OUTPUT));
}

Model *modelShift = Model::create<ShiftModule, ShiftWidget>("Shift");
