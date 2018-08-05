#include "../controller/CV.hpp"

#include "../../deps/rack-components/screws.hpp"
#include "components.hpp"

struct CVWidget : ModuleWidget {
  CVWidget(CVModule *module);
};

CVWidget::CVWidget(CVModule *module) : ModuleWidget(module) {
  box.size = Vec(2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/CV.svg")));
    addChild(panel);
  }

  addChild(Widget::create<JLHHexScrew>(Vec(8.5, 1)));
  addChild(Widget::create<JLHHexScrew>(Vec(8.5, 366)));

  for (int i = 0; i < CV_COUNT; i++) {
    addParam(ParamWidget::create<CDLEDBezel>(Vec(3, 30 + (190 * i)), module,
                                          CVModule::SWITCH + i, 0.0f,
                                          1.0f, 0.0f));
    addChild(ModuleLightWidget::create<CDButtonLight<GreenLight>>(
        Vec(5.2, 32 + (190 * i)), module, CVModule::OUT_LIGHT + i));

    addParam(ParamWidget::create<LightKnobSmall>(Vec(5, 80 + (190 * i)), module, CVModule::KNOB + i,
                                       0.0f, 10.0f, 0.0f));

    addOutput(Port::create<CDPort>(Vec(1, 130 + (190 * i)), Port::OUTPUT, module,
                                   CVModule::OUT + i));
  }
}

Model *modelCV = Model::create<CVModule, CVWidget>("CharredDesert", "CV",
                                                      "CV", LOGIC_TAG);
