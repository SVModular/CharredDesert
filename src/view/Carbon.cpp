#include "../controller/Carbon.hpp"

#include "../../deps/rack-components/display.hpp"
#include "../../deps/rack-components/screws.hpp"
#include "components.hpp"

struct CarbonWidget : ModuleWidget {
  CarbonWidget(CarbonModule *module);
};

CarbonWidget::CarbonWidget(CarbonModule *module) : ModuleWidget(module) {
  box.size = Vec(4 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/Carbon.svg")));
    addChild(panel);
  }


  {
    FrequencyDisplay *frequency = new FrequencyDisplay();
    frequency->value = &module->frequency;
    frequency->box.pos = Vec(5.5, 46);
    frequency->box.size = Vec(40, 18);
    addChild(frequency);
  }

  addInput(Port::create<CDPort>(Vec(17.5, 35), Port::INPUT, module,
                                CarbonModule::AUDIO_INPUT));

  addParam(ParamWidget::create<LightKnob>(
      Vec(28.5, 104.5), module, CarbonModule::FREQ_PARAM, 20.0f, 6000.0f, (6000 - 20) / 2));
  addInput(Port::create<CDPort>(Vec(4, 110), Port::INPUT, module,
                                CarbonModule::FREQ_INPUT));

  addParam(ParamWidget::create<LightKnob>(
      Vec(28.5, 154.5), module, CarbonModule::REZ_PARAM, 0.0f, 4.0f, 2.0f));
  addInput(Port::create<CDPort>(Vec(4, 160), Port::INPUT, module,
                                CarbonModule::REZ_INPUT));

  addOutput(Port::create<CDPort>(Vec(17.5, 210), Port::OUTPUT, module, CarbonModule::AUDIO_OUTPUT));
}

Model *modelCarbon = Model::create<CarbonModule, CarbonWidget>("CharredDesert", "Carbon", "Carbon", FILTER_TAG);
