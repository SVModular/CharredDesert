#include "../controller/Eq.hpp"

#include "../../deps/rack-components/display.hpp"
#include "components.hpp"

struct EqWidget : ModuleWidget {
  EqWidget(EqModule *module);
};

EqWidget::EqWidget(EqModule *module) : ModuleWidget(module) {
  box.size = Vec(4 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(pluginInstance, "res/Eq.svg")));
    addChild(panel);
  }

  {
    FrequencyDisplay *frequency = new FrequencyDisplay();
    if (module) {
      fprintf(stderr, "eq value => %x\n", &module->frequency);
      frequency->value = &module->frequency;
    }
    frequency->box.pos = Vec(5.5, 46);
    frequency->box.size = Vec(40, 18);
    addChild(frequency);
  }

  {
    EqTypeDisplay *type = new EqTypeDisplay();
    if (module) {
      fprintf(stderr, "eq display => %x, %d\n", &module->filterType, module->filterType);
      type->value = &module->filterType;
    }
    type->box.pos = Vec(5.5, 81);
    type->box.size = Vec(40, 18);
    addChild(type);
  }


  addParam(createParam<LightKnob>(
      Vec(28.5, 104.5), module, EqModule::FREQ_PARAM, 30.0f, 14000.0f, 7000.0f));
  addInput(createPort<CDPort>(Vec(4, 110), PortWidget::INPUT, module,
                                EqModule::FREQ_CV_INPUT));
  addParam(createParam<LightKnobSnap>(
      Vec(17.5, 179.5), module, EqModule::TYPE_PARAM, 0.0f, 6.0f, 0.0f));
  addParam(createParam<LightKnob>(Vec(28.5, 229.5), module,
                                          EqModule::Q_PARAM, 0.1f, 6.0f, 0.1f));
  addInput(createPort<CDPort>(Vec(4, 235), PortWidget::INPUT, module,
                                EqModule::Q_CV_INPUT));


  addInput(createPort<CDPort>(Vec(0, 35), PortWidget::INPUT, module,
                                EqModule::AUDIO_INPUT));
  addOutput(createPort<CDPort>(Vec(35, 35), PortWidget::OUTPUT, module,
                                 EqModule::AUDIO_OUTPUT));
}

Model *modelEq = createModel<EqModule, EqWidget>("Eq");
