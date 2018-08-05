#include "../controller/M.hpp"

#include "../../deps/rack-components/screws.hpp"
#include "components.hpp"

struct MWidget : ModuleWidget {
  MWidget(MModule *module);
};

MWidget::MWidget(MModule *module) : ModuleWidget(module) {
  box.size = Vec(2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/M.svg")));
    addChild(panel);
  }

  addChild(Widget::create<JLHHexScrew>(Vec(8.5, 1)));
  addChild(Widget::create<JLHHexScrew>(Vec(8.5, 366)));

  for (int i = 0; i < M_COUNT; i++) {
    addInput(Port::create<CDPort>(Vec(3, 30 + (190 * i)), Port::INPUT, module,
                                   MModule::IN1 + i));

    addInput(Port::create<CDPort>(Vec(3, 65 + (190 * i)), Port::INPUT, module,
                                   MModule::IN2 + i));

    addParam(ParamWidget::create<LightKnobSmall>(Vec(5, 102 + (190 * i)), module, MModule::KNOB + i,
                                       0.0f, 1.0f, 0.5f));

    addOutput(Port::create<CDPort>(Vec(3, 140 + (190 * i)), Port::OUTPUT, module,
                                   MModule::OUT + i));
  }
}

Model *modelM = Model::create<MModule, MWidget>("CharredDesert", "M",
                                                      "M", MIXER_TAG);
