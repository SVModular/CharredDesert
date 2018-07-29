#include "../controller/CVSeq.hpp"

#include "../../deps/rack-components/screws.hpp"
#include "components.hpp"

struct CVSeqWidget : ModuleWidget {
  CVSeqWidget(CVSeqModule *module);
};

CVSeqWidget::CVSeqWidget(CVSeqModule *module) : ModuleWidget(module) {
  box.size = Vec(4 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/CVSeq.svg")));
    addChild(panel);
  }

  addChild(Widget::create<JLHHexScrew>(Vec(23.5, 1)));
  addChild(Widget::create<JLHHexScrew>(
      Vec(23.5, 366)));

  addInput(Port::create<CDPort>(Vec(4, 35), Port::INPUT, module, CVSeqModule::CV_INPUT));
  addOutput(Port::create<CDPort>(Vec(32, 35), Port::OUTPUT, module, CVSeqModule::CV_OUTPUT));

  addInput(Port::create<CDPort>(Vec(4, 85), Port::INPUT, module, CVSeqModule::KNOB1_INPUT));
  addParam(ParamWidget::create<LightKnobSnap>(Vec(28.5, 79.5), module, CVSeqModule::KNOB1, 0.0f, 10.0f, 0.0f));

  addInput(Port::create<CDPort>(Vec(4, 135), Port::INPUT, module, CVSeqModule::KNOB2_INPUT));
  addParam(ParamWidget::create<LightKnobSnap>(Vec(28.5, 129.5), module, CVSeqModule::KNOB2, 0.0f, 10.0f, 0.0f));

  addInput(Port::create<CDPort>(Vec(4, 185), Port::INPUT, module, CVSeqModule::KNOB3_INPUT));
  addParam(ParamWidget::create<LightKnobSnap>(Vec(28.5, 179.5), module, CVSeqModule::KNOB3, 0.0f, 10.0f, 0.0f));

  addInput(Port::create<CDPort>(Vec(4, 235), Port::INPUT, module, CVSeqModule::KNOB4_INPUT));
  addParam(ParamWidget::create<LightKnobSnap>(Vec(28.5, 229.5), module, CVSeqModule::KNOB4, 0.0f, 10.0f, 0.0f));

  addChild(ModuleLightWidget::create<MediumLight<RedLight>>(Vec(36, 109), module,
                                              CVSeqModule::LED1));
  addChild(ModuleLightWidget::create<MediumLight<RedLight>>(Vec(36, 159), module,
                                              CVSeqModule::LED2));
  addChild(ModuleLightWidget::create<MediumLight<RedLight>>(Vec(36, 209), module,
                                              CVSeqModule::LED3));
  addChild(ModuleLightWidget::create<MediumLight<RedLight>>(Vec(36, 259), module,
                                              CVSeqModule::LED4));
}

Model *modelCVSeq = Model::create<CVSeqModule, CVSeqWidget>("CharredDesert", "CV Sequencer", "CV Sequencer", LOGIC_TAG, SEQUENCER_TAG, LOGIC_TAG);
