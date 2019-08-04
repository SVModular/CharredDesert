#include "Tine.hpp"

#define VALUE(a) (a.isConnected() ? a.getVoltage() : 0.0f)

TineModule::TineModule() {
  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
  configParam(POLARITY, 0, 1, 0);
  configParam(SPLIT, 0, 10, 5);
  configParam(LOWER_ATT, -10, 10, 0);
  configParam(UPPER_ATT, -10, 10, 0);

  id = messages->registerMember();
}

TineModule::~TineModule() {
  messages->deregisterMember(id);
}

float TineModule::paramValue (uint16_t param, uint16_t input, float low, float high) {
  float current = params[param].getValue();

  if (inputs[input].isConnected()) {
    // high - low, divided by one tenth input voltage, plus the current value
    current += ((inputs[input].getVoltage() / 10) * (high - low));
  }

  return clamp(current, low, high);
}


void TineModule::process(const ProcessArgs &args) {
  outputs[LOWER_OUT].setVoltage(0);
  outputs[UPPER_OUT].setVoltage(0);
  lights[LOWER_LIGHT].value = 0;
  lights[UPPER_LIGHT].value = 0;

  if (inputs[MODIFIER_IN].isConnected()) {
    bool uni = params[POLARITY].getValue() ? true : false;

    float split = paramValue(SPLIT, SPLIT_CV, 0, 10);
    float lower = paramValue(LOWER_ATT, LOWER_ATT_CV, -10, 10);
    float upper = paramValue(UPPER_ATT, UPPER_ATT_CV, -10, 10);

    if (!uni) {
      split -= 5.0f;
    }

    float modifier = inputs[MODIFIER_IN].getVoltage();
    float audio = inputs[AUDIO_IN].isConnected() ? inputs[AUDIO_IN].getVoltage() : modifier;

    if (modifier < split) {
      outputs[LOWER_OUT].setVoltage(audio + lower);
      lights[LOWER_LIGHT].value = 1;
    } else {
      outputs[UPPER_OUT].setVoltage(audio + upper);
      lights[UPPER_LIGHT].value = 1;
    }
  }

  Payload payload;
  payload.values[0] = outputs[LOWER_OUT].getVoltage();
  payload.values[1] = outputs[UPPER_OUT].getVoltage();
  Message<Payload> *message = new Message<Payload>();
  message->value = payload;

  messages->send(id, message);
}
