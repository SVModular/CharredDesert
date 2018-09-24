#include "../controller/DTMF.hpp"

#include "../../deps/rack-components/jacks.hpp"
#include "../../deps/rack-components/screws.hpp"
#include "components.hpp"

struct DTMFWidget : ModuleWidget {
  DTMFWidget(DTMFModule *module);
};

DTMFWidget::DTMFWidget(DTMFModule *module) : ModuleWidget(module) {
  box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/DTMF.svg")));
    addChild(panel);
  }


  addInput(Port::create<CDPort>(Vec(10, 35), Port::INPUT, module,
                                DTMFModule::CV_INPUT));
  addInput(Port::create<CDPort>(Vec(10, 85), Port::INPUT, module,
                                DTMFModule::VOCT_INPUT));
  addOutput(Port::create<CDPort>(Vec(10, 135), Port::OUTPUT, module,
                                 DTMFModule::AUDIO_OUTPUT));
  addChild(ModuleLightWidget::create<MediumLight<RedLight>>(
      Vec(18, 209), module, DTMFModule::ON_LED));
}

Model *modelDTMF = Model::create<DTMFModule, DTMFWidget>(
    "CharredDesert", "DTMF", "DTMF", ENVELOPE_GENERATOR_TAG);
