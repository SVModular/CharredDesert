#include "../controller/CV.hpp"

#include "components.hpp"

struct CVWidget : ModuleWidget {
  CVWidget(CVModule *module);
};

CVWidget::CVWidget(CVModule *module) : ModuleWidget(module) {
  box.size = Vec(2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(pluginInstance, "res/CV.svg")));
    addChild(panel);
  }


  for (int i = 0; i < CV_COUNT; i++) {
    addParam(createParam<CDLEDBezel>(Vec(4, 35 + (190 * i)), module,
                                          CVModule::SWITCH + i, 0.0f,
                                          1.0f, 0.0f));
    addChild(createLight<CDButtonLight<GreenLight>>(
        Vec(5.2, 37 + (190 * i)), module, CVModule::OUT_LIGHT + i));

    addParam(createParam<LightKnobSmall>(Vec(5, 85 + (190 * i)), module, CVModule::KNOB + i,
                                       0.0f, 10.0f, 0.0f));

    addOutput(createPort<CDPort>(Vec(3, 135 + (190 * i)), PortWidget::OUTPUT, module,
                                   CVModule::OUT + i));
  }
}

Model *modelCV = createModel<CVModule, CVWidget>("CV");
