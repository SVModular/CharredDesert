#include "../controller/Noise.hpp"

#include "components.hpp"

struct NoiseWidget : ModuleWidget {
  NoiseWidget(NoiseModule *module);
};

NoiseWidget::NoiseWidget(NoiseModule *module) {
  setModule(module);
  box.size = Vec(3 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Noise.svg")));

  addInput(createInput<CDPort>(Vec(10, 35), module,
                                NoiseModule::CV_INPUT));
  addParam(createParam<CKSS>(Vec(15, 95), module,
                                     NoiseModule::NOISE_SWITCH));
  addOutput(createOutput<CDPort>(Vec(10, 135), module,
                                 NoiseModule::AUDIO_OUTPUT));
  addChild(createLight<MediumLight<RedLight>>(
      Vec(18, 209), module, NoiseModule::ON_LED));
}

Model *modelNoise = createModel<NoiseModule, NoiseWidget>("Noise");
