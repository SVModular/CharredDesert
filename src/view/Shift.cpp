#include "../controller/Shift.hpp"

#include "components.hpp"

struct ShiftWidget : ModuleWidget {
  ShiftWidget(ShiftModule *module);
};

ShiftWidget::ShiftWidget(ShiftModule *module) {
  setModule(module);
  box.size = Vec(4 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Shift.svg")));


  addInput(createInput<CDPort>(Vec(17.5, 35), module,
                                ShiftModule::INPUT));
  addParam(createParam<CKSS>(Vec(22.5, 95), module, ShiftModule::SWITCH));

  addParam(createParam<LightKnob>(
      Vec(28.5, 154.5), module, ShiftModule::KNOB));
  addInput(createInput<CDPort>(Vec(4, 160), module,
                                ShiftModule::SHIFT));
  addOutput(createOutput<CDPort>(Vec(17.5, 211), module,
                                 ShiftModule::OUTPUT));
}

Model *modelShift = createModel<ShiftModule, ShiftWidget>("Shift");
