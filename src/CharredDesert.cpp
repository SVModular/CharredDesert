#include "CharredDesert.hpp"

// The plugin-wide instance of the Plugin class
Plugin *plugin;

void init(rack::Plugin *p) {
  plugin = p;
  // This is the unique identifier for your plugin
  p->slug = "CharredDesert";
#ifdef VERSION
  p->version = TOSTRING(VERSION);
#endif
  p->website = "https://github.com/JerrySievert/CharredDesert";
  p->manual  = "https://github.com/JerrySievert/CharredDesert/blob/master/README.md";

  // For each module, specify the ModuleWidget subclass, manufacturer slug (for
  // saving in patches), manufacturer human-readable name, module slug, and
  // module name
  p->addModel(createModel<DTMFWidget>("CharredDesert", "DTMF", "DTMF"));
  p->addModel(createModel<NoiseWidget>("CharredDesert", "Noise", "Noise"));
}
