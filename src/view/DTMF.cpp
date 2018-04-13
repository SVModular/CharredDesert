#include "../controller/DTMF.hpp"

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

  addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(Widget::create<ScrewSilver>(
      Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

  addInput(Port::create<RCJackSmallRed>(Vec(10, 45), Port::INPUT, module, DTMFModule::CV_INPUT));
  addInput(Port::create<RCJackSmallRed>(Vec(10, 100), Port::INPUT, module, DTMFModule::VOCT_INPUT));
  addOutput(Port::create<RCJackSmallRed>(Vec(10, 165), Port::OUTPUT, module, DTMFModule::AUDIO_OUTPUT));
  addChild(ModuleLightWidget::create<MediumLight<RedLight>>(Vec(18, 220), module,
                                              DTMFModule::ON_LED));
}

Model *modelDTMF = Model::create<DTMFModule, DTMFWidget>("CharredDesert", "DTMF", "DTMF", ENVELOPE_GENERATOR_TAG);
