#include "../controller/Oscar.hpp"

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
