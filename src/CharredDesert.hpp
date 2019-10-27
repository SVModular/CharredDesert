#include "rack.hpp"

using namespace rack;

extern Plugin *pluginInstance;

struct Payload {
  float values[8];
};


////////////////////
// module widgets
////////////////////

extern Model *modelDTMF;
extern Model *modelNoise;
extern Model *modelNot;
extern Model *modelPan;
extern Model *modelShift;
extern Model *modelCVSeq;
extern Model *modelOscar2;
extern Model *modelEq;
extern Model *modelCarbon;
extern Model *modelMixer;
extern Model *modelMixerCV;
extern Model *modelCV;
extern Model *modelM;
extern Model *modelTine;
extern Model *modelK;
extern Model *modelX;
extern Model *modelTsunami;
