#include <cstdint>

#include "CharredDesert.hpp"
#include "components/custom.hpp"
#include "rack.hpp"

struct ShiftModule : Module {
  enum ParamIds { SWITCH, KNOB, NUM_PARAMS };
  enum InputIds { INPUT, NUM_INPUTS };
  enum OutputIds { OUTPUT, NUM_OUTPUTS };
  enum LightIds { NUM_LIGHTS };

  ShiftModule() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) { }

  void step() override;
};

void ShiftModule::step() {
  float in = inputs[INPUT].value;

  float shift = params[KNOB].value;

  if (params[SWITCH].value) {
    outputs[OUTPUT].value = clampf(in + shift, -5.0f, 5.0f);
  } else {
    outputs[OUTPUT].value = in + shift;
  }
}

ShiftWidget::ShiftWidget() {
  ShiftModule *module = new ShiftModule();
  setModule(module);
  box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/Shift.svg")));
    addChild(panel);
  }

  addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(createScrew<ScrewSilver>(
      Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

  addInput(createInput<Jack>(Vec(10, 45), module, ShiftModule::INPUT));
  addParam(createParam<CKSS>(Vec(15, 112), module, ShiftModule::SWITCH,
                             0.0f, 1.0f, 0.0f));
  addParam(createParam<Davies1900hRedKnob>(Vec(5, 165), module,
                                          ShiftModule::KNOB, -5.0f, 5.0f, 0.0f));
  addOutput(
      createOutput<Jack>(Vec(10, 230), module, ShiftModule::OUTPUT));
}
