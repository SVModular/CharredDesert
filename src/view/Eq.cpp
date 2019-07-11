#include "../controller/Eq.hpp"

#include "components.hpp"

struct EqWidget : ModuleWidget {
  EqWidget(EqModule *module);
};

EqWidget::EqWidget(EqModule *module) {
  setModule(module);
  box.size = Vec(4 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Eq.svg")));

  {
    FrequencyDisplay *frequency = new FrequencyDisplay();
    if (module) {
      frequency->value = &module->frequency;
    }
    frequency->box.pos = Vec(5.5, 46);
    frequency->box.size = Vec(40, 18);
    addChild(frequency);
  }

  {
    EqTypeDisplay *type = new EqTypeDisplay();
    if (module) {
      type->value = &module->filterType;
    }
    type->box.pos = Vec(5.5, 81);
    type->box.size = Vec(40, 18);
    addChild(type);
  }


  addParam(createParam<LightKnob>(
      Vec(28.5, 104.5), module, EqModule::FREQ_PARAM));

  addInput(createInput<CDPort>(Vec(4, 110), module,
                                EqModule::FREQ_CV_INPUT));
  addParam(createParam<LightKnobSnap>(
      Vec(17.5, 179.5), module, EqModule::TYPE_PARAM));
  addParam(createParam<LightKnob>(Vec(28.5, 229.5), module,
                                          EqModule::Q_PARAM));

  addInput(createInput<CDPort>(Vec(4, 235), module,
                                EqModule::Q_CV_INPUT));


  addInput(createInput<CDPort>(Vec(0, 35), module,
                                EqModule::AUDIO_INPUT));
  addOutput(createOutput<CDPort>(Vec(35, 35), module,
                                 EqModule::AUDIO_OUTPUT));
}

Model *modelEq = createModel<EqModule, EqWidget>("Eq");
