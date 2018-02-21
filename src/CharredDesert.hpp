#include "rack.hpp"

using namespace rack;

extern Plugin *plugin;

////////////////////
// module widgets
////////////////////

struct SidViciousWidget : ModuleWidget {
  SidViciousWidget();
};

extern Model *modelDTMF;
extern Model *modelNoise;
extern Model *modelNot;
extern Model *modelPan;
extern Model *modelShift;
extern Model *modelCVSeq;