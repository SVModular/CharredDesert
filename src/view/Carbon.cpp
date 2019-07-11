#include "../controller/Carbon.hpp"

#include "components.hpp"

struct CarbonWidget : ModuleWidget {
  CarbonWidget(CarbonModule *module);
};

CarbonWidget::CarbonWidget(CarbonModule *module) {
  setModule(module);
  box.size = Vec(4 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Carbon.svg")));


  {
    FrequencyDisplay *frequency = new FrequencyDisplay();
    if (module) {
      frequency->value = &module->frequency;
    }
    frequency->box.pos = Vec(5.5, 46);
    frequency->box.size = Vec(40, 18);
    addChild(frequency);
  }

  addInput(createInput<CDPort>(Vec(17.5, 35), module,
                                CarbonModule::AUDIO_INPUT));

  addParam(createParam<LightKnob>(
      Vec(28.5, 104.5), module, CarbonModule::FREQ_PARAM));

  addInput(createInput<CDPort>(Vec(4, 110), module,
                                CarbonModule::FREQ_INPUT));

  addParam(createParam<LightKnob>(
      Vec(28.5, 154.5), module, CarbonModule::REZ_PARAM));

  addInput(createInput<CDPort>(Vec(4, 160), module,
                                CarbonModule::REZ_INPUT));

  addOutput(createOutput<CDPort>(Vec(17.5, 210), module, CarbonModule::AUDIO_OUTPUT));
}

Model *modelCarbon = createModel<CarbonModule, CarbonWidget>("Carbon");
