#include "../controller/CVSeq.hpp"

#include "components.hpp"

struct CVSeqWidget : ModuleWidget {
  CVSeqWidget(CVSeqModule *module);
};

CVSeqWidget::CVSeqWidget(CVSeqModule *module) : ModuleWidget(module) {
  box.size = Vec(4 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(pluginInstance, "res/CVSeq.svg")));
    addChild(panel);
  }


  addInput(createPort<CDPort>(Vec(4, 35), PortWidget::INPUT, module,
                                CVSeqModule::CV_INPUT));
  addOutput(createPort<CDPort>(Vec(32, 35), PortWidget::OUTPUT, module,
                                 CVSeqModule::CV_OUTPUT));

  addInput(createPort<CDPort>(Vec(4, 85), PortWidget::INPUT, module,
                                CVSeqModule::KNOB1_INPUT));
  addParam(createParam<LightKnobSnap>(
      Vec(28.5, 79.5), module, CVSeqModule::KNOB1, 0.0f, 10.0f, 0.0f));

  addInput(createPort<CDPort>(Vec(4, 135), PortWidget::INPUT, module,
                                CVSeqModule::KNOB2_INPUT));
  addParam(createParam<LightKnobSnap>(
      Vec(28.5, 129.5), module, CVSeqModule::KNOB2, 0.0f, 10.0f, 0.0f));

  addInput(createPort<CDPort>(Vec(4, 185), PortWidget::INPUT, module,
                                CVSeqModule::KNOB3_INPUT));
  addParam(createParam<LightKnobSnap>(
      Vec(28.5, 179.5), module, CVSeqModule::KNOB3, 0.0f, 10.0f, 0.0f));

  addInput(createPort<CDPort>(Vec(4, 235), PortWidget::INPUT, module,
                                CVSeqModule::KNOB4_INPUT));
  addParam(createParam<LightKnobSnap>(
      Vec(28.5, 229.5), module, CVSeqModule::KNOB4, 0.0f, 10.0f, 0.0f));

  addChild(createLight<MediumLight<RedLight>>(
      Vec(36, 109), module, CVSeqModule::LED1));
  addChild(createLight<MediumLight<RedLight>>(
      Vec(36, 159), module, CVSeqModule::LED2));
  addChild(createLight<MediumLight<RedLight>>(
      Vec(36, 209), module, CVSeqModule::LED3));
  addChild(createLight<MediumLight<RedLight>>(
      Vec(36, 259), module, CVSeqModule::LED4));
}

Model *modelCVSeq = createModel<CVSeqModule, CVSeqWidget>("CVSequencer");
