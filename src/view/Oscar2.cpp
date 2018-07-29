#include "../controller/Oscar2.hpp"

#include "../../deps/rack-components/display.hpp"
#include "../../deps/rack-components/screws.hpp"
#include "components.hpp"

struct Oscar2Widget : ModuleWidget {
  Oscar2Widget(Oscar2Module *module);
};

Oscar2Widget::Oscar2Widget(Oscar2Module *module) : ModuleWidget(module) {
  box.size = Vec(10 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/Oscar2.svg")));
    addChild(panel);
  }

  addChild(Widget::create<JLHHexScrew>(Vec(1, 1)));
  addChild(Widget::create<JLHHexScrew>(Vec(136, 1)));
  addChild(Widget::create<JLHHexScrew>(Vec(1, 366)));
  addChild(Widget::create<JLHHexScrew>(Vec(136, 366)));
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
		waveSelect->box.pos = Vec(9.5, 33);
		waveSelect->box.size = Vec(10, 10);
		addChild(waveSelect);
	}

  // shape - left
  addInput(Port::create<CDPort>(Vec(4, 85), Port::INPUT, module, Oscar2Module::SHAPE_INPUT1));
  addParam(ParamWidget::create<LightKnobSnap>(Vec(28.5, 79.5), module, Oscar2Module::SHAPE_PARAM1, 0.0f, 3.0f, 0.0f));

  // shift - left
  addInput(Port::create<CDPort>(Vec(4, 135), Port::INPUT, module, Oscar2Module::SHIFT_INPUT1));
  addParam(ParamWidget::create<LightKnob>(Vec(28.5, 129.5), module, Oscar2Module::SHIFT_PARAM1, 0.0f, 10.0f, 0.0f));

  // octave - left
  addInput(Port::create<CDPort>(Vec(4, 185), Port::INPUT, module, Oscar2Module::OCTAVE_INPUT1));
  addParam(ParamWidget::create<LightKnobSnap>(Vec(28.5, 179.5), module, Oscar2Module::OCTAVE_PARAM1, -4.0f, 4.0f, 0.0f));

  // fine - left
  addInput(Port::create<CDPort>(Vec(4, 235), Port::INPUT, module, Oscar2Module::FINE_INPUT1));
  addParam(ParamWidget::create<LightKnob>(Vec(28.5, 229.5), module, Oscar2Module::FINE_PARAM1, -1.0f, 1.0f, 0.0f));

  // random - left
  addInput(Port::create<CDPort>(Vec(4, 285), Port::INPUT, module, Oscar2Module::RANDOM_INPUT1));
  addParam(ParamWidget::create<LightKnob>(Vec(28.5, 279.5), module, Oscar2Module::RANDOM_PARAM1, 0.0f, 5.0f, 0.0f));

  // invert - left
  addParam(ParamWidget::create<CKSS>(Vec(67, 108), module, Oscar2Module::INVERT_PARAM1, 0.0f, 1.0f, 1.0f));

  // wave selection - right
  {
		WaveSelect *waveSelect = new WaveSelect();
		waveSelect->value = &module->wave2;
		waveSelect->box.pos = Vec(55, 33);
		waveSelect->box.size = Vec(10, 10);
		addChild(waveSelect);
	}

  // shape - right
  addInput(Port::create<CDPort>(Vec(94, 85), Port::INPUT, module, Oscar2Module::SHAPE_INPUT2));
  addParam(ParamWidget::create<LightKnobSnap>(Vec(118.5, 79.5), module, Oscar2Module::SHAPE_PARAM2, 0.0f, 3.0f, 0.0f));

  // shift - right
  addInput(Port::create<CDPort>(Vec(94, 135), Port::INPUT, module, Oscar2Module::SHIFT_INPUT2));
  addParam(ParamWidget::create<LightKnob>(Vec(118.5, 129.5), module, Oscar2Module::SHIFT_PARAM2, 0.0f, 10.0f, 0.0f));

  // octave - right
  addInput(Port::create<CDPort>(Vec(94, 185), Port::INPUT, module, Oscar2Module::OCTAVE_INPUT2));
  addParam(ParamWidget::create<LightKnobSnap>(Vec(118.5, 179.5), module, Oscar2Module::OCTAVE_PARAM2, -4.0f, 4.0f, 0.0f));

  // fine - right
  addInput(Port::create<CDPort>(Vec(94, 235), Port::INPUT, module, Oscar2Module::FINE_INPUT2));
  addParam(ParamWidget::create<LightKnob>(Vec(118.5, 229.5), module, Oscar2Module::FINE_PARAM2, -1.0f, 1.0f, 0.0f));

  // random - right
  addInput(Port::create<CDPort>(Vec(94, 285), Port::INPUT, module, Oscar2Module::RANDOM_INPUT2));
  addParam(ParamWidget::create<LightKnob>(Vec(118.5, 279.5), module, Oscar2Module::RANDOM_PARAM2, 0.0f, 5.0f, 0.0f));

  // invert - right
  addParam(ParamWidget::create<CKSS>(Vec(67, 158), module, Oscar2Module::INVERT_PARAM2, 0.0f, 1.0f, 1.0f));

  // mix
  addInput(Port::create<CDPort>(Vec(62.5, 227), Port::INPUT, module, Oscar2Module::MIX_INPUT));
  addParam(ParamWidget::create<LightKnob>(Vec(62.5, 252.5), module, Oscar2Module::MIX_PARAM, 0.0f, 10.0f, 5.0f));

  // v/oct
  addInput(Port::create<CDPort>(Vec(22.5, 330), Port::INPUT, module,
                                        Oscar2Module::FREQ_INPUT));


  // mix out
  addOutput(Port::create<CDPort>(Vec(102.5, 330), Port::OUTPUT, module,
                                         Oscar2Module::AUDIO_OUTPUT));



}

Model *modelOscar2 =
    Model::create<Oscar2Module, Oscar2Widget>("CharredDesert", "Oscar^2", "Oscar^2", OSCILLATOR_TAG, WAVESHAPER_TAG);
