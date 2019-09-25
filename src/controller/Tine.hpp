#include <cstdint>
#include <string>

#include "../CharredDesert.hpp"

struct TineModule : Module {
  enum ParamIds {
    POLARITY,
    SPLIT,
    LOWER_ATT,
    UPPER_ATT,
    NUM_PARAMS
  };
  enum InputIds {
    AUDIO_IN,
    MODIFIER_IN,
    SPLIT_CV,
    LOWER_ATT_CV,
    UPPER_ATT_CV,
    NUM_INPUTS
  };
  enum OutputIds {
    LOWER_OUT,
    UPPER_OUT,
    NUM_OUTPUTS
  };
  enum LightIds {
    LOWER_LIGHT,
    UPPER_LIGHT,
    NUM_LIGHTS
  };

  TineModule( );
  float paramValue (uint16_t, uint16_t, float, float);

  void process(const ProcessArgs &args) override;

  std::string id;
};
