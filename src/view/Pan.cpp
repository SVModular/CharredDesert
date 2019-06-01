#include "../controller/Pan.hpp"

#include "../../deps/rack-components/screws.hpp"
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


  addInput(Port::create<CDPort>(Vec(17.5, 35), Port::INPUT, module,
                                PanModule::AUDIO_INPUT));
  addParam(ParamWidget::create<LightKnob>(
      Vec(28.5, 79.5), module, PanModule::PAN_PARAM, -5.0f, 5.0f, 0.0f));
  addInput(Port::create<CDPort>(Vec(4, 85), Port::INPUT, module,
                                PanModule::PAN_INPUT));
  addOutput(Port::create<CDPort>(Vec(17.5, 135), Port::OUTPUT, module,
                                 PanModule::AUDIO_OUTPUT1));
  addOutput(Port::create<CDPort>(Vec(17.5, 185), Port::OUTPUT, module,
                                 PanModule::AUDIO_OUTPUT2));
}

Model *modelPan = Model::create<PanModule, PanWidget>("Pan");
