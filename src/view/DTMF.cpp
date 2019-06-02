#include "../controller/DTMF.hpp"

#include "components.hpp"

struct DTMFWidget : ModuleWidget {
  DTMFWidget(DTMFModule *module);
};

DTMFWidget::DTMFWidget(DTMFModule *module) : ModuleWidget(module) {
  box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(pluginInstance, "res/DTMF.svg")));
    addChild(panel);
  }


  addInput(createPort<CDPort>(Vec(10, 35), PortWidget::INPUT, module,
                                DTMFModule::CV_INPUT));
  addInput(createPort<CDPort>(Vec(10, 85), PortWidget::INPUT, module,
                                DTMFModule::VOCT_INPUT));
  addOutput(createPort<CDPort>(Vec(10, 135), PortWidget::OUTPUT, module,
                                 DTMFModule::AUDIO_OUTPUT));
  addChild(createLight<MediumLight<RedLight>>(
      Vec(18, 209), module, DTMFModule::ON_LED));
}

Model *modelDTMF = createModel<DTMFModule, DTMFWidget>("DTMF");
