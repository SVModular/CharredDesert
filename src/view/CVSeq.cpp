#include "../controller/CVSeq.hpp"

#include "components.hpp"

struct CVSeqWidget : ModuleWidget {
  CVSeqWidget(CVSeqModule *module);
};

CVSeqWidget::CVSeqWidget(CVSeqModule *module) {
  setModule(module);
  box.size = Vec(4 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CVSeq.svg")));


  addInput(createInput<CDPort>(Vec(4, 35), module,
                                CVSeqModule::CV_INPUT));
  addOutput(createOutput<CDPort>(Vec(32, 35), module,
                                 CVSeqModule::CV_OUTPUT));

  addInput(createInput<CDPort>(Vec(4, 85), module,
                                CVSeqModule::KNOB1_INPUT));
  addParam(createParam<LightKnobSnap>(
      Vec(28.5, 79.5), module, CVSeqModule::KNOB1));

  addInput(createInput<CDPort>(Vec(4, 135), module,
                                CVSeqModule::KNOB2_INPUT));
  addParam(createParam<LightKnobSnap>(
      Vec(28.5, 129.5), module, CVSeqModule::KNOB2));

  addInput(createInput<CDPort>(Vec(4, 185), module,
                                CVSeqModule::KNOB3_INPUT));
  addParam(createParam<LightKnobSnap>(
      Vec(28.5, 179.5), module, CVSeqModule::KNOB3));

  addInput(createInput<CDPort>(Vec(4, 235), module,
                                CVSeqModule::KNOB4_INPUT));
  addParam(createParam<LightKnobSnap>(
      Vec(28.5, 229.5), module, CVSeqModule::KNOB4));

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
