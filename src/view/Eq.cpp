#include "../controller/Eq.hpp"

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
		frequency->box.pos = Vec(2, 20);
		frequency->box.size = Vec(40, 18);
		addChild(frequency);
	}

  {
		EqTypeDisplay *type = new EqTypeDisplay();
		type->value = &module->filterType;
		type->box.pos = Vec(2, 52);
		type->box.size = Vec(40, 18);
		addChild(type);
	}

  addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
  addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
  addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

  addParam(ParamWidget::create<RCKnobRed>(Vec(8, 53), module, EqModule::FREQ_PARAM, 30.0f, 14000.0f, 7000.0f));
  addParam(ParamWidget::create<RCKnobRedSnap>(Vec(8, 125), module, EqModule::TYPE_PARAM, 0.0f, 6.0f, 0.0f));
  addParam(ParamWidget::create<RCKnobRed>(Vec(8, 169), module, EqModule::Q_PARAM, 0.0f, 2.0f, 0.0f));

  addInput(Port::create<RCJackSmallRed>(Vec(10, 225), Port::INPUT, module, EqModule::AUDIO_INPUT));
  addOutput(Port::create<RCJackSmallRed>(Vec(10, 265), Port::OUTPUT, module, EqModule::AUDIO_OUTPUT));
}

Model *modelEq = Model::create<EqModule, EqWidget>("CharredDesert", "Eq", "Eq", EQUALIZER_TAG);
