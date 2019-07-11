#include "../controller/CV.hpp"

#include "components.hpp"

struct CVWidget : ModuleWidget {
  CVWidget(CVModule *module);
};

CVWidget::CVWidget(CVModule *module) {
  setModule(module);
  box.size = Vec(2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CV.svg")));


  for (int i = 0; i < CV_COUNT; i++) {
    addParam(createParam<CDLEDBezel>(Vec(4, 35 + (190 * i)), module,
                                          CVModule::SWITCH + i));

    addChild(createLight<CDButtonLight<GreenLight>>(
        Vec(5.2, 37 + (190 * i)), module, CVModule::OUT_LIGHT + i));

    addParam(createParam<LightKnobSmall>(Vec(5, 85 + (190 * i)), module, CVModule::KNOB + i));

    addOutput(createOutput<CDPort>(Vec(3, 135 + (190 * i)), module,
                                   CVModule::OUT + i));
  }
}

Model *modelCV = createModel<CVModule, CVWidget>("CV");
