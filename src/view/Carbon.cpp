#include "../controller/Carbon.hpp"

#include "../../deps/rack-components/display.hpp"
#include "components.hpp"

struct CarbonWidget : ModuleWidget {
  CarbonWidget(CarbonModule *module);
};

CarbonWidget::CarbonWidget(CarbonModule *module) : ModuleWidget(module) {
  box.size = Vec(4 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(pluginInstance, "res/Carbon.svg")));
    addChild(panel);
  }


  {
    FrequencyDisplay *frequency = new FrequencyDisplay();
    if (module) {
      fprintf(stderr, "carbon value => %x\n", &module->frequency);
      frequency->value = &module->frequency;
    }
    frequency->box.pos = Vec(5.5, 46);
    frequency->box.size = Vec(40, 18);
    addChild(frequency);
  }

  addInput(createPort<CDPort>(Vec(17.5, 35), PortWidget::INPUT, module,
                                CarbonModule::AUDIO_INPUT));

  addParam(createParam<LightKnob>(
      Vec(28.5, 104.5), module, CarbonModule::FREQ_PARAM, 20.0f, 6000.0f, (6000 - 20) / 2));
  addInput(createPort<CDPort>(Vec(4, 110), PortWidget::INPUT, module,
                                CarbonModule::FREQ_INPUT));

  addParam(createParam<LightKnob>(
      Vec(28.5, 154.5), module, CarbonModule::REZ_PARAM, 0.0f, 4.0f, 2.0f));
  addInput(createPort<CDPort>(Vec(4, 160), PortWidget::INPUT, module,
                                CarbonModule::REZ_INPUT));

  addOutput(createPort<CDPort>(Vec(17.5, 210), PortWidget::OUTPUT, module, CarbonModule::AUDIO_OUTPUT));
}

Model *modelCarbon = createModel<CarbonModule, CarbonWidget>("Carbon");
