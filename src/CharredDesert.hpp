#include "rack.hpp"

using namespace rack;

extern Plugin *plugin;

////////////////////
// module widgets
////////////////////

struct SidViciousWidget : ModuleWidget {
  SidViciousWidget();
};

struct DTMFWidget : ModuleWidget {
  DTMFWidget();
};

struct NoiseWidget : ModuleWidget {
  NoiseWidget();
};

struct CVSeqWidget : ModuleWidget {
  CVSeqWidget();
};
