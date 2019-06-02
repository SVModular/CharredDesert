#include "../CharredDesert.hpp"

#include "../../deps/SynthDevKit/src/CV.hpp"

#define CV_COUNT 2

struct CVModule : Module {
  enum ParamIds { KNOB, SWITCH = CV_COUNT, NUM_PARAMS = CV_COUNT * 2 };
  enum InputIds {  NUM_INPUTS };
  enum OutputIds { OUT, NUM_OUTPUTS = CV_COUNT };
  enum LightIds { OUT_LIGHT, NUM_LIGHTS = CV_COUNT };

  CVModule();

  void step() override;

  bool on[CV_COUNT];

  SynthDevKit::CV *cv[CV_COUNT];

  json_t *dataToJson() override {
    json_t *rootJ = json_object();

    json_t *arr = json_array();

    for (int i = 0; i < CV_COUNT; i++) {
      json_array_append(arr, json_boolean(on[i]));
    }

    json_object_set_new(rootJ, "switches", arr);

    return rootJ;
  }

  void dataFromJson(json_t *rootJ) override {
    json_t *switchJ = json_object_get(rootJ, "switches");

    if (switchJ && json_is_array(switchJ)) {
      for (int i = 0; i < CV_COUNT; i++) {
        json_t *v = json_array_get(switchJ, i);
        if (v) {
          on[i] = json_boolean_value(v);
        }
      }
    }
  }

};
