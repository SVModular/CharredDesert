#include <cstdint>

#include "../deps/SynthDevKit/src/CV.hpp"
#include "../deps/rack-components/jacks.hpp"
#include "../deps/rack-components/knobs.hpp"
#include "CharredDesert.hpp"
#include "LFO.hpp"

struct OscarModule : Module {
  enum ParamIds {
    MIX_PARAM1,
    MIX_PARAM2,
    MIX_PARAM3,
    MIX_PARAM4,
    MIX_PARAM5,
    MIX_PARAM6,
    NUM_PARAMS
  };
  enum InputIds {
    MIX_INPUT1,
    MIX_INPUT2,
    MIX_INPUT3,
    MIX_INPUT4,
    MIX_INPUT5,
    MIX_INPUT6,
    FREQ_INPUT,
    NUM_INPUTS
  };
  enum OutputIds {
    AUDIO_OUTPUT1,
    AUDIO_OUTPUT2,
    AUDIO_OUTPUT3,
    AUDIO_OUTPUT4,
    AUDIO_OUTPUT5,
    AUDIO_OUTPUT6,
    NUM_OUTPUTS
  };
  enum LightIds { NUM_LIGHTS };

  OscarModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
    osc = new LowFrequencyOscillator();
  }

  LowFrequencyOscillator *osc;
  void step() override;
};

static float calculateFrequency(float voltage) {
  return 261.626f * powf(2.0f, voltage);
}

static float calculateMix(float input, float param) {
  return clamp((input + param), 0.0f, 10.0f);
}

void OscarModule::step() {
  float freq = inputs[FREQ_INPUT].value;

  osc->setPitch(calculateFrequency(freq));
  osc->step(engineGetSampleTime());

  outputs[AUDIO_OUTPUT1].value = 5.0f * ((osc->sin() * ((10 - calculateMix(inputs[MIX_INPUT1].value, params[MIX_PARAM1].value)) / 10) + (osc->tri() * (calculateMix(inputs[MIX_INPUT1]. value, params[MIX_PARAM1].value) / 10))));
  outputs[AUDIO_OUTPUT2].value = 5.0f * ((osc->sin() * ((10 - calculateMix(inputs[MIX_INPUT2].value, params[MIX_PARAM2].value)) / 10) + (osc->saw() * (calculateMix(inputs[MIX_INPUT2]. value, params[MIX_PARAM2].value) / 10))));
  outputs[AUDIO_OUTPUT3].value = 5.0f * ((osc->tri() * ((10 - calculateMix(inputs[MIX_INPUT3].value, params[MIX_PARAM3].value)) / 10) + (osc->saw() * (calculateMix(inputs[MIX_INPUT3]. value, params[MIX_PARAM3].value) / 10))));
}

struct OscarWidget : ModuleWidget {
  OscarWidget(OscarModule *module);
};

OscarWidget::OscarWidget(OscarModule *module) : ModuleWidget(module) {
  box.size = Vec(6 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/Oscar.svg")));
    addChild(panel);
  }

  addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(Widget::create<ScrewSilver>(
      Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

  addInput(Port::create<RCJackSmallRed>(Vec(16, 21), Port::INPUT, module,
                                        OscarModule::FREQ_INPUT));

  // sine - triangle
  addParam(ParamWidget::create<RCKnobRed>(Vec(3, 73), module, OscarModule::MIX_PARAM1, 0.0f, 10.0f, 5.0f));
  addInput(Port::create<RCJackSmallRed>(Vec(38, 77), Port::INPUT, module, OscarModule::MIX_INPUT1));

  addOutput(Port::create<RCJackSmallRed>(Vec(65, 77), Port::OUTPUT, module,
                                         OscarModule::AUDIO_OUTPUT1));


  // sine - saw
  addParam(ParamWidget::create<RCKnobRed>(Vec(3, 143), module, OscarModule::MIX_PARAM2, 0.0f, 10.0f, 5.0f));
  addInput(Port::create<RCJackSmallRed>(Vec(38, 147), Port::INPUT, module, OscarModule::MIX_INPUT2));

  addOutput(Port::create<RCJackSmallRed>(Vec(65, 147), Port::OUTPUT, module,
                                        OscarModule::AUDIO_OUTPUT2));

  // triangle - saw
  addParam(ParamWidget::create<RCKnobRed>(Vec(3, 213), module, OscarModule::MIX_PARAM3, 0.0f, 10.0f, 5.0f));
  addInput(Port::create<RCJackSmallRed>(Vec(38, 217), Port::INPUT, module, OscarModule::MIX_INPUT3));

  addOutput(Port::create<RCJackSmallRed>(Vec(65, 217), Port::OUTPUT, module,
                                        OscarModule::AUDIO_OUTPUT3));

}

Model *modelOscar =
    Model::create<OscarModule, OscarWidget>("CharredDesert", "Oscar", "Oscar", OSCILLATOR_TAG, WAVESHAPER_TAG);
