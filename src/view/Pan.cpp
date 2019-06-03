#include "../controller/Pan.hpp"

#include "components.hpp"

struct PanWidget : ModuleWidget {
  PanWidget(PanModule *module);
};

PanWidget::PanWidget(PanModule *module) {
  setModule(module);
  box.size = Vec(4 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Pan.svg")));


  addInput(createInput<CDPort>(Vec(17.5, 35), module,
                                PanModule::AUDIO_INPUT));
  addParam(createParam<LightKnob>(
      Vec(28.5, 79.5), module, PanModule::PAN_PARAM));
  addInput(createInput<CDPort>(Vec(4, 85), module,
                                PanModule::PAN_INPUT));
  addOutput(createOutput<CDPort>(Vec(17.5, 135), module,
                                 PanModule::AUDIO_OUTPUT1));
  addOutput(createOutput<CDPort>(Vec(17.5, 185), module,
                                 PanModule::AUDIO_OUTPUT2));
}

Model *modelPan = createModel<PanModule, PanWidget>("Pan");
