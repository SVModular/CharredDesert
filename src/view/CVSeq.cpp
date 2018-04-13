#include "../controller/CVSeq.hpp"

struct CVSeqWidget : ModuleWidget {
  CVSeqWidget(CVSeqModule *module);
};

CVSeqWidget::CVSeqWidget(CVSeqModule *module) : ModuleWidget(module) {
  box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/CVSeq.svg")));
    addChild(panel);
  }

  addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(Widget::create<ScrewSilver>(
      Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

  addInput(Port::create<RCJackSmallRed>(Vec(0, 24), Port::INPUT, module, CVSeqModule::CV_INPUT));
  addOutput(Port::create<RCJackSmallRed>(Vec(20, 24), Port::OUTPUT, module, CVSeqModule::CV_OUTPUT));

  addParam(ParamWidget::create<RCKnobRedLarge>(Vec(5, 80), module,
                                           CVSeqModule::KNOB1, 0.0, 10.0, 0.0));
  addParam(ParamWidget::create<RCKnobRedLarge>(Vec(5, 130), module,
                                           CVSeqModule::KNOB2, 0.0, 10.0, 0.0));
  addParam(ParamWidget::create<RCKnobRedLarge>(Vec(5, 180), module,
                                           CVSeqModule::KNOB3, 0.0, 10.0, 0.0));
  addParam(ParamWidget::create<RCKnobRedLarge>(Vec(5, 230), module,
                                           CVSeqModule::KNOB4, 0.0, 10.0, 0.0));
  addChild(ModuleLightWidget::create<MediumLight<RedLight>>(Vec(33, 114), module,
                                              CVSeqModule::LED1));
  addChild(ModuleLightWidget::create<MediumLight<RedLight>>(Vec(33, 164), module,
                                              CVSeqModule::LED2));
  addChild(ModuleLightWidget::create<MediumLight<RedLight>>(Vec(33, 214), module,
                                              CVSeqModule::LED3));
  addChild(ModuleLightWidget::create<MediumLight<RedLight>>(Vec(33, 264), module,
                                              CVSeqModule::LED4));
}

Model *modelCVSeq = Model::create<CVSeqModule, CVSeqWidget>("CharredDesert", "CV Sequencer", "CV Sequencer", LOGIC_TAG, SEQUENCER_TAG, LOGIC_TAG);
