#include "../controller/M.hpp"

#include "components.hpp"

struct MWidget : ModuleWidget {
  MWidget(MModule *module);
};

MWidget::MWidget(MModule *module) : ModuleWidget(module) {
  box.size = Vec(2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(pluginInstance, "res/M.svg")));
    addChild(panel);
  }


  for (int i = 0; i < M_COUNT; i++) {
    addInput(createPort<CDPort>(Vec(3, 30 + (190 * i)), PortWidget::INPUT, module,
                                   MModule::IN1 + i));

    addInput(createPort<CDPort>(Vec(3, 65 + (190 * i)), PortWidget::INPUT, module,
                                   MModule::IN2 + i));

    addParam(createParam<LightKnobSmall>(Vec(5, 102 + (190 * i)), module, MModule::KNOB + i,
                                       0.0f, 1.0f, 0.5f));

    addOutput(createPort<CDPort>(Vec(3, 140 + (190 * i)), PortWidget::OUTPUT, module,
                                   MModule::OUT + i));
  }
}

Model *modelM = createModel<MModule, MWidget>("M");
