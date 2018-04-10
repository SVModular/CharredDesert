#include <cstdint>

#include "../deps/SynthDevKit/src/CV.hpp"
#include "../deps/rack-components/jacks.hpp"
#include "../deps/rack-components/knobs.hpp"
#include "../deps/rack-components/display.hpp"
#include "CharredDesert.hpp"
#include "LFO.hpp"

struct Oscar2Module : Module {
  enum ParamIds {
    SHAPE_PARAM1,
    SHAPE_PARAM2,
    SHIFT_PARAM1,
    SHIFT_PARAM2,
    OCTAVE_PARAM1,
    OCTAVE_PARAM2,
    FINE_PARAM1,
    FINE_PARAM2,
    RANDOM_PARAM1,
    RANDOM_PARAM2,
    MIX_PARAM,
    INVERT_PARAM1,
    INVERT_PARAM2,
    NUM_PARAMS
  };
  enum InputIds {
    SHAPE_INPUT1,
    SHAPE_INPUT2,
    SHIFT_INPUT1,
    SHIFT_INPUT2,
    OCTAVE_INPUT1,
    OCTAVE_INPUT2,
    FINE_INPUT1,
    FINE_INPUT2,
    RANDOM_INPUT1,
    RANDOM_INPUT2,
    MIX_INPUT,
    FREQ_INPUT,
    NUM_INPUTS
  };
  enum OutputIds {
    AUDIO_OUTPUT,
    NUM_OUTPUTS
  };
  enum LightIds { NUM_LIGHTS };

  Oscar2Module() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
    osc1 = new LowFrequencyOscillator;
    osc2 = new LowFrequencyOscillator;
  }

  void step() override;

  float shift1 = 0.0f;
  float shift2 = 0.0f;
  uint8_t wave1 = 0;
  uint8_t wave2 = 0;
  LowFrequencyOscillator *osc1;
  LowFrequencyOscillator *osc2;
  float value = 0.0f;
};

static float calculateFrequency(float voltage) {
  return 261.626f * powf(2.0f, voltage);
}

static float calculateMix(float input, float param) {
  return clamp((input + param), 0.0f, 10.0f);
}

static float calculateShift(float frequency, float percent) {
  return (frequency * (percent / 100));
}

static float valueForWave(LowFrequencyOscillator *osc, uint8_t wave) {
  if (wave == 0) {
    return osc->sin();
  } else if (wave == 1) {
    return osc->tri();
  } else if (wave == 2) {
    return osc->saw();
  } else if (wave == 3) {
    return osc->sqr();
  } else {
    return 0.0f;
  }
}

void Oscar2Module::step() {
  float freq = inputs[FREQ_INPUT].value;

  osc1->setInvert(params[INVERT_PARAM1].value ? false : true);
  osc2->setInvert(params[INVERT_PARAM2].value ? false : true);

  float w1 = clamp(params[SHAPE_PARAM1].value + inputs[SHAPE_INPUT1].value, 0.0f, 3.0f);
  wave1 = (uint8_t) w1;

  float s1 = clamp(params[SHIFT_PARAM1].value + inputs[SHIFT_INPUT1].value, 0.0f, 10.0f) * 10;

  if (s1 != shift1) {
    osc1->setShift(calculateShift(calculateFrequency(freq), s1));
    osc1->hardReset();
    osc2->hardReset();
    shift1 = s1;
  }

  float octave1 = params[OCTAVE_PARAM1].value + inputs[OCTAVE_INPUT1].value;
  float fine1 = params[FINE_PARAM1].value + (inputs[FINE_INPUT1].value / 2);

  float freq1 = clamp(freq + octave1 + fine1, -5.0f, 5.0f);
  osc1->setFrequency(calculateFrequency(freq1));

  float rand1 = clamp(params[RANDOM_PARAM1].value + (inputs[RANDOM_INPUT1].value / 2), 0.0f, 5.0f);
  osc1->setRandom(rand1);

  float w2 = clamp(params[SHAPE_PARAM2].value + inputs[SHAPE_INPUT2].value, 0.0f, 3.0f);
  wave2 = (uint8_t) w2;

  float s2 = clamp(params[SHIFT_PARAM2].value + inputs[SHIFT_INPUT2].value, 0.0f, 10.0f) * 10;

  if (s2 != shift2) {
    osc2->setShift(calculateShift(calculateFrequency(freq), s1));
    osc2->hardReset();
    osc1->hardReset();
    shift2 = s2;
  }

  float octave2 = params[OCTAVE_PARAM2].value + inputs[OCTAVE_INPUT2].value;
  float fine2 = params[FINE_PARAM2].value + (inputs[FINE_INPUT2].value / 2);

  float freq2 = clamp(freq + octave2 + fine2, -5.0f, 5.0f);
  osc2->setFrequency(calculateFrequency(freq2));

  float rand2 = clamp(params[RANDOM_PARAM2].value + (inputs[RANDOM_INPUT2].value / 2), 0.0f, 5.0f);
  osc2->setRandom(rand2);


  osc1->step(engineGetSampleTime());
  osc2->step(engineGetSampleTime());

  float left = valueForWave(osc1, wave1);
  float right = valueForWave(osc2, wave2);

  outputs[AUDIO_OUTPUT].value = 5.0f * ((left * ((10 - calculateMix(inputs[MIX_INPUT].value, params[MIX_PARAM].value)) / 10) + (right * (calculateMix(inputs[MIX_INPUT]. value, params[MIX_PARAM].value) / 10))));
}

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
  addChild(Widget::create<ScrewSilver>(
      Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
  addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH-12, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH + 12, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

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
