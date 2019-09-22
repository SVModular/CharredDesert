#include "rack.hpp"
#include "model/MessageBus.hpp"

using namespace rack;

extern Plugin *pluginInstance;

struct Payload {
  float values[8];
};

extern MessageBus<Payload> *messages;

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
