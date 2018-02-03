#include <cstdint>

#include "rack.hpp"
#include "CharredDesert.hpp"
#include "../deps/SynthDevKit/src/CV.hpp"
#include "components/custom.hpp"

struct CVSeqModule : Module {
  enum ParamIds { KNOB1, KNOB2, KNOB3, KNOB4, NUM_PARAMS };
  enum InputIds { CV_INPUT, NUM_INPUTS };
  enum OutputIds { CV_OUTPUT, NUM_OUTPUTS };
  enum LightIds { LED1, LED2, LED3, LED4, NUM_LIGHTS };

  CVSeqModule( ) : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
    cv = new SynthDevKit::CV(1.7f);
    currentStep = 0;
  }

  void step( ) override;

  SynthDevKit::CV *cv;
  uint8_t currentStep;
};

void CVSeqModule::step( ) {
  float cv_in = inputs[CV_INPUT].value;
  float current = 0.0f;

  cv->update(cv_in);

  if (cv->newTrigger()) {
    current = params[currentStep].value;
    outputs[CV_OUTPUT].value = current;
    for (int i = 0; i < 4; i++) {
      if (i == currentStep) {
        lights[i].value = 1.0;
      } else {
        lights[i].value = 0.0;
      }
    }
    currentStep++;

    if (currentStep == 4) {
      currentStep = 0;
    }
  }
}

CVSeqWidget::CVSeqWidget( ) {
  CVSeqModule *module = new CVSeqModule( );
  setModule(module);
  box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel( );
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/CVSeq.svg")));
    addChild(panel);
  }

  addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(createScrew<ScrewSilver>(
      Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

  addInput(
      createInput<Jack>(Vec(0, 24), module, CVSeqModule::CV_INPUT));
  addOutput(
      createOutput<Jack>(Vec(20, 24), module, CVSeqModule::CV_OUTPUT));

  addParam(
      createParam<Davies1900hRedKnob>(Vec(5, 80), module, CVSeqModule::KNOB1, 0.0, 10.0, 0.0)
  );
  addParam(
      createParam<Davies1900hRedKnob>(Vec(5, 130), module, CVSeqModule::KNOB2, 0.0, 10.0, 0.0)
  );
  addParam(
      createParam<Davies1900hRedKnob>(Vec(5, 180), module, CVSeqModule::KNOB3, 0.0, 10.0, 0.0)
  );
  addParam(
      createParam<Davies1900hRedKnob>(Vec(5, 230), module, CVSeqModule::KNOB4, 0.0, 10.0, 0.0)
  );
  addChild(
      createLight<MediumLight<RedLight>>(Vec(33, 114), module, CVSeqModule::LED1));
  addChild(
      createLight<MediumLight<RedLight>>(Vec(33, 164), module, CVSeqModule::LED2));
  addChild(
      createLight<MediumLight<RedLight>>(Vec(33, 214), module, CVSeqModule::LED3));
  addChild(
      createLight<MediumLight<RedLight>>(Vec(33, 264), module, CVSeqModule::LED4));

}
