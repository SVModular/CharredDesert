#include "../controller/Noise.hpp"

struct NoiseWidget : ModuleWidget {
  NoiseWidget(NoiseModule *module);
};

NoiseWidget::NoiseWidget(NoiseModule *module) : ModuleWidget(module) {
  box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(plugin, "res/Noise.svg")));
    addChild(panel);
  }

  addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
  addChild(Widget::create<ScrewSilver>(
      Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

  addInput(Port::create<RCJackSmallRed>(Vec(10, 45), Port::INPUT, module, NoiseModule::CV_INPUT));
  addParam(ParamWidget::create<CKSS>(Vec(15, 112), module, NoiseModule::NOISE_SWITCH,
                             0.0, 1.0, 1.0));
  addOutput(
      Port::create<RCJackSmallRed>(Vec(10, 165), Port::OUTPUT, module, NoiseModule::AUDIO_OUTPUT));
  addChild(ModuleLightWidget::create<MediumLight<RedLight>>(Vec(18, 220), module,
                                              NoiseModule::ON_LED));
}

Model *modelNoise = Model::create<NoiseModule, NoiseWidget>("CharredDesert", "Noise", "Noise", NOISE_TAG);
