#include "../controller/DTMF.hpp"

#include "components.hpp"

struct DTMFWidget : ModuleWidget {
  DTMFWidget(DTMFModule *module);
};

DTMFWidget::DTMFWidget(DTMFModule *module) {
  setModule(module);
  box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/DTMF.svg")));


  addInput(createInput<CDPort>(Vec(10, 35), module,
                                DTMFModule::CV_INPUT));
  addInput(createInput<CDPort>(Vec(10, 85), module,
                                DTMFModule::VOCT_INPUT));
  addOutput(createOutput<CDPort>(Vec(10, 135), module,
                                 DTMFModule::AUDIO_OUTPUT));
  addChild(createLight<MediumLight<RedLight>>(
      Vec(18, 209), module, DTMFModule::ON_LED));
}

Model *modelDTMF = createModel<DTMFModule, DTMFWidget>("DTMF");
