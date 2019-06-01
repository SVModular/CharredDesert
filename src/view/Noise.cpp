#include "../controller/Noise.hpp"

#include "../../deps/rack-components/screws.hpp"
#include "components.hpp"

struct NoiseWidget : ModuleWidget {
  NoiseWidget(NoiseModule *module);
};

NoiseWidget::NoiseWidget(NoiseModule *module) : ModuleWidget(module) {
  box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  {
    SVGPanel *panel = new SVGPanel();
    panel->box.size = box.size;
    panel->setBackground(SVG::load(assetPlugin(pluginInstance, "res/Noise.svg")));
    addChild(panel);
  }


  addInput(Port::create<CDPort>(Vec(10, 35), Port::INPUT, module,
                                NoiseModule::CV_INPUT));
  addParam(ParamWidget::create<CKSS>(Vec(15, 95), module,
                                     NoiseModule::NOISE_SWITCH, 0.0, 1.0, 1.0));
  addOutput(Port::create<CDPort>(Vec(10, 135), Port::OUTPUT, module,
                                 NoiseModule::AUDIO_OUTPUT));
  addChild(ModuleLightWidget::create<MediumLight<RedLight>>(
      Vec(18, 209), module, NoiseModule::ON_LED));
}

Model *modelNoise = Model::create<NoiseModule, NoiseWidget>("Noise");
