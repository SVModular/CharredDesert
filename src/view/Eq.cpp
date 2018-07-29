#include "../controller/Eq.hpp"

#include "../../deps/rack-components/jacks.hpp"
#include "../../deps/rack-components/screws.hpp"
#include "../../deps/rack-components/display.hpp"
#include "components.hpp"

struct EqWidget : ModuleWidget {
  EqWidget(EqModule *module);
};

EqWidget::EqWidget(EqModule *module) : ModuleWidget(module) {
  box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/Eq.svg")));
    addChild(panel);
  }

  {
		FrequencyDisplay *frequency = new FrequencyDisplay();
		frequency->value = &module->frequency;
    frequency->box.pos = Vec(1, 46);
		frequency->box.size = Vec(40, 18);
		addChild(frequency);
	}

  {
		EqTypeDisplay *type = new EqTypeDisplay();
		type->value = &module->filterType;
    type->box.pos = Vec(1, 81);
		type->box.size = Vec(40, 18);
		addChild(type);
	}

  addChild(Widget::create<JLHHexScrew>(Vec(16, 1)));
  addChild(Widget::create<JLHHexScrew>(
      Vec(16, 366)));

  addParam(ParamWidget::create<LightKnob>(Vec(10, 104.5), module, EqModule::FREQ_PARAM, 30.0f, 14000.0f, 7000.0f));
  addParam(ParamWidget::create<LightKnobSnap>(Vec(10, 179.5), module, EqModule::TYPE_PARAM, 0.0f, 6.0f, 0.0f));
  addParam(ParamWidget::create<LightKnob>(Vec(10, 229.5), module, EqModule::Q_PARAM, 0.0f, 2.0f, 0.0f));

  addInput(Port::create<CDPort>(Vec(0, 35), Port::INPUT, module, EqModule::AUDIO_INPUT));
  addOutput(Port::create<CDPort>(Vec(20, 35), Port::OUTPUT, module, EqModule::AUDIO_OUTPUT));
}

Model *modelEq = Model::create<EqModule, EqWidget>("CharredDesert", "Eq", "Eq", EQUALIZER_TAG);
