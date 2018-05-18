#include "../controller/Oscar2.hpp"

struct Oscar2Widget : ModuleWidget {
  Oscar2Widget(Oscar2Module *module);
};

Oscar2Widget::Oscar2Widget(Oscar2Module *module) : ModuleWidget(module) {
  box.size = Vec(12 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/Oscar2.svg")));
    addChild(panel);
  }

  addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
  addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
  addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
/*
  {
    ValueDisplay *vd = new ValueDisplay();
    vd->value = &module->value;
    vd->box.pos = Vec(35, 142);
    vd->box.size = Vec(10, 10);
    addChild(vd);
  }
*/
  // wave selection - left
  {
		WaveSelect *waveSelect = new WaveSelect();
		waveSelect->value = &module->wave1;
		waveSelect->box.pos = Vec(17, 42);
		waveSelect->box.size = Vec(10, 10);
		addChild(waveSelect);
	}

  // shape - left
  addInput(Port::create<RCJackSmallRed>(Vec(18, 104), Port::INPUT, module, Oscar2Module::SHAPE_INPUT1));
  addParam(ParamWidget::create<RCKnobRedSnap>(Vec(42, 96), module, Oscar2Module::SHAPE_PARAM1, 0.0f, 3.0f, 0.0f));

  // shift - left
  addInput(Port::create<RCJackSmallRed>(Vec(18, 150), Port::INPUT, module, Oscar2Module::SHIFT_INPUT1));
  addParam(ParamWidget::create<RCKnobRed>(Vec(42, 142), module, Oscar2Module::SHIFT_PARAM1, 0.0f, 10.0f, 0.0f));

  // octave - left
  addInput(Port::create<RCJackSmallRed>(Vec(18, 196), Port::INPUT, module, Oscar2Module::OCTAVE_INPUT1));
  addParam(ParamWidget::create<RCKnobRedSnap>(Vec(42, 188), module, Oscar2Module::OCTAVE_PARAM1, -4.0f, 4.0f, 0.0f));

  // fine - left
  addInput(Port::create<RCJackSmallRed>(Vec(18, 242), Port::INPUT, module, Oscar2Module::FINE_INPUT1));
  addParam(ParamWidget::create<RCKnobRed>(Vec(42, 236), module, Oscar2Module::FINE_PARAM1, -1.0f, 1.0f, 0.0f));

  // random - left
  addInput(Port::create<RCJackSmallRed>(Vec(18, 288), Port::INPUT, module, Oscar2Module::RANDOM_INPUT1));
  addParam(ParamWidget::create<RCKnobRed>(Vec(42, 280), module, Oscar2Module::RANDOM_PARAM1, 0.0f, 5.0f, 0.0f));

  // invert - left
  addParam(ParamWidget::create<CKSS>(Vec(87, 108), module, Oscar2Module::INVERT_PARAM1, 0.0f, 1.0f, 1.0f));

  // wave selection - right
  {
		WaveSelect *waveSelect = new WaveSelect();
		waveSelect->value = &module->wave2;
		waveSelect->box.pos = Vec(65, 42);
		waveSelect->box.size = Vec(10, 10);
		addChild(waveSelect);
	}

  // shape - right
  addInput(Port::create<RCJackSmallRed>(Vec(113, 104), Port::INPUT, module, Oscar2Module::SHAPE_INPUT2));
  addParam(ParamWidget::create<RCKnobRedSnap>(Vec(137, 96), module, Oscar2Module::SHAPE_PARAM2, 0.0f, 3.0f, 0.0f));

  // shift - right
  addInput(Port::create<RCJackSmallRed>(Vec(113, 150), Port::INPUT, module, Oscar2Module::SHIFT_INPUT2));
  addParam(ParamWidget::create<RCKnobRed>(Vec(137, 142), module, Oscar2Module::SHIFT_PARAM2, 0.0f, 10.0f, 0.0f));

  // octave - right
  addInput(Port::create<RCJackSmallRed>(Vec(113, 196), Port::INPUT, module, Oscar2Module::OCTAVE_INPUT2));
  addParam(ParamWidget::create<RCKnobRedSnap>(Vec(137, 188), module, Oscar2Module::OCTAVE_PARAM2, -4.0f, 4.0f, 0.0f));

  // fine - right
  addInput(Port::create<RCJackSmallRed>(Vec(113, 242), Port::INPUT, module, Oscar2Module::FINE_INPUT2));
  addParam(ParamWidget::create<RCKnobRed>(Vec(137, 236), module, Oscar2Module::FINE_PARAM2, -1.0f, 1.0f, 0.0f));

  // random - right
  addInput(Port::create<RCJackSmallRed>(Vec(113, 288), Port::INPUT, module, Oscar2Module::RANDOM_INPUT2));
  addParam(ParamWidget::create<RCKnobRed>(Vec(137, 280), module, Oscar2Module::RANDOM_PARAM2, 0.0f, 5.0f, 0.0f));

  // invert - right
  addParam(ParamWidget::create<CKSS>(Vec(87, 170), module, Oscar2Module::INVERT_PARAM2, 0.0f, 1.0f, 1.0f));

  // mix
  addInput(Port::create<RCJackSmallRed>(Vec(68, 38), Port::INPUT, module, Oscar2Module::MIX_INPUT));
  addParam(ParamWidget::create<RCKnobRed>(Vec(92, 30), module, Oscar2Module::MIX_PARAM, 0.0f, 10.0f, 5.0f));

  // v/oct
  addInput(Port::create<RCJackSmallRed>(Vec(12, 38), Port::INPUT, module,
                                        Oscar2Module::FREQ_INPUT));


  // mix out
  addOutput(Port::create<RCJackSmallRed>(Vec(147, 38), Port::OUTPUT, module,
                                         Oscar2Module::AUDIO_OUTPUT));



}

Model *modelOscar2 =
    Model::create<Oscar2Module, Oscar2Widget>("CharredDesert", "Oscar^2", "Oscar^2", OSCILLATOR_TAG, WAVESHAPER_TAG);
