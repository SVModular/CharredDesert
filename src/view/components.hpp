#pragma once
/*
Shadow code taken and modified from https://github.com/lindenbergresearch/LRTRack

and is available under the following license:

Copyright (c) 2017-2018, Lindenberg Research / Patrick Lindenberg
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Commercial redistribution of the code, or parts, in any form
  must be granted by the author.

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of Lindenberg Research nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.


THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

struct CDShadow {
private:
  Rect box;
  float size = 0.65;
  float strength = 0.8f;

  Vec shadowPos = Vec(3, 5);

public:
  void setShadowPosition(float x, float y) {
    shadowPos = Vec(x, y);
  }

  void setBox(const Rect &box) {
    CDShadow::box = box;
  }

  void setSize(float size) {
    CDShadow::size = size;
  }

  void setStrength(float strength) {
    CDShadow::strength = strength;
  }

  void drawShadow(NVGcontext *vg, float strength, float size) {
    // add shadow
    nvgBeginPath(vg);
    nvgRect(vg, -20, -20, box.size.x + 40, box.size.y + 40);

    NVGcolor icol = nvgRGBAf(0.0f, 0.0f, 0.0f, strength);
    NVGcolor ocol = nvgRGBAf(0.0f, 0.0f, 0.0f, 0.f);
    ;

    NVGpaint paint = nvgRadialGradient(
        vg, box.size.x / 2 + shadowPos.x, box.size.y / 2 + shadowPos.y,
        box.size.x * 0.3f, box.size.x * size, icol, ocol);
    nvgFillPaint(vg, paint);
    nvgFill(vg);
  }

  void draw(NVGcontext *vg) {
    drawShadow(vg, strength, size);
  };
};

struct CDKnob : RoundKnob {
protected:
  CDShadow shadow = CDShadow();

public:
  CDKnob() {
  }

  void setSVG(std::shared_ptr<SVG> svg) {
    app::SvgKnob::setSVG(svg);

    shadow.setBox(box);
  }

  void draw(const DrawArgs &args) override {
    /** shadow */
    shadow.draw(args.vg);

    /** component */
    app::SvgKnob::draw(args);
  }
};

struct LightKnob : CDKnob {
  LightKnob() {
    setSVG(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Knob.svg")));
  }
};

struct LightKnobSnap : LightKnob {
  LightKnobSnap() {
    snap = true;
  }
};

struct LightKnobSmall : CDKnob {
  LightKnobSmall() {
    setSVG(APP->window->loadSvg(asset::plugin(pluginInstance, "res/KnobSmall.svg")));
  }
};

struct CDPort : app::SvgPort {
private:
  CDShadow shadow = CDShadow();

public:
  CDPort() {
    setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Port.svg")));

    /** inherit dimensions */
    shadow.setBox(box);
    shadow.setSize(0.4);
    shadow.setShadowPosition(2, 1);
  }

  void draw(const DrawArgs &args) override {
    shadow.draw(args.vg);
    app::SvgPort::draw(args);
  }
};

struct CDLEDDisplay : TransparentWidget {
private:
  CDShadow shadow = CDShadow();

public:
  float *value;

	CDLEDDisplay ( ) {
    value = NULL;

    /** inherit dimensions */
    shadow.setBox(box);
    shadow.setSize(0.4);
    shadow.setShadowPosition(2, 1);
  }

  void draw (const DrawArgs &args) override {
    NVGcolor red = nvgRGBA(192, 0, 0, 255);
    NVGcolor yellow = nvgRGBA(255, 192, 0, 255);
    NVGcolor green = nvgRGBA(0, 192, 0, 255);
    NVGcolor grey = nvgRGBA(80, 80, 80, 255);
    float val = value ? *value : 0.0f;

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 0, 8, 8);
    if (fabs(val) >= 4.5) {
      nvgFillColor(args.vg, red);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);


    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 11, 8, 8);
    if (fabs(val) >= 4.0) {
      nvgFillColor(args.vg, yellow);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 22, 8, 8);
    if (fabs(val) >= 3.5) {
      nvgFillColor(args.vg, yellow);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 33, 8, 8);
    if (fabs(val) >= 3.0) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 44, 8, 8);
    if (fabs(val) >= 2.5) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 55, 8, 8);
    if (fabs(val) >= 2.0) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 66, 8, 8);
    if (fabs(val) >= 1.5) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 77, 8, 8);
    if (fabs(val) >= 1.0) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 88, 8, 8);
    if (fabs(val) >= 0.5) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 99, 8, 8);
    if (fabs(val) > 0.0) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    shadow.draw(args.vg);
  }
};

struct CDLEDSmallDisplay : TransparentWidget {
private:
  CDShadow shadow = CDShadow();

public:
  float *value = NULL;

	CDLEDSmallDisplay ( ) {
    value = NULL;

    /** inherit dimensions */
    shadow.setBox(box);
    shadow.setSize(0.4);
    shadow.setShadowPosition(2, 1);
  }

  void draw (const DrawArgs &args) override {
    NVGcolor red = nvgRGBA(192, 0, 0, 255);
    NVGcolor yellow = nvgRGBA(255, 192, 0, 255);
    NVGcolor green = nvgRGBA(0, 192, 0, 255);
    NVGcolor grey = nvgRGBA(80, 80, 80, 255);

    float val = value ? *value : 0.0f;

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 0, 8, 6);
    if (fabs(val) >= 4.5) {
      nvgFillColor(args.vg, red);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);


    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 8, 8, 6);
    if (fabs(val) >= 4.0) {
      nvgFillColor(args.vg, yellow);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 16, 8, 6);
    if (fabs(val) >= 3.5) {
      nvgFillColor(args.vg, yellow);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 24, 8, 6);
    if (fabs(val) >= 3.0) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 32, 8, 6);
    if (fabs(val) >= 2.5) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 40, 8, 6);
    if (fabs(val) >= 2.0) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 48, 8, 6);
    if (fabs(val) >= 1.5) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 56, 8, 6);
    if (fabs(val) >= 1.0) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 64, 8, 6);
    if (fabs(val) >= 0.5) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 72, 8, 6);
    if (fabs(val) > 0.0) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    shadow.draw(args.vg);
  }
};

struct CDLEDWideDisplay : TransparentWidget {
private:
  CDShadow shadow = CDShadow();

public:
  float *value = NULL;

	CDLEDWideDisplay ( ) {
    value = NULL;

    /** inherit dimensions */
    shadow.setBox(box);
    shadow.setSize(0.4);
    shadow.setShadowPosition(2, 1);
  }

  void draw (const DrawArgs &args) override {
    NVGcolor red = nvgRGBA(192, 0, 0, 255);
    NVGcolor yellow = nvgRGBA(255, 192, 0, 255);
    NVGcolor green = nvgRGBA(0, 192, 0, 255);
    NVGcolor grey = nvgRGBA(80, 80, 80, 255);

    float val = value ? *value : 0.0f;

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 0, 16, 8);
    if (fabs(val) >= 4.5) {
      nvgFillColor(args.vg, red);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);


    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 11, 16, 8);
    if (fabs(val) >= 4.0) {
      nvgFillColor(args.vg, yellow);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 22, 16, 8);
    if (fabs(val) >= 3.5) {
      nvgFillColor(args.vg, yellow);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 33, 16, 8);
    if (fabs(val) >= 3.0) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 44, 16, 8);
    if (fabs(val) >= 2.5) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 55, 16, 8);
    if (fabs(val) >= 2.0) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 66, 16, 8);
    if (fabs(val) >= 1.5) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 77, 16, 8);
    if (fabs(val) >= 1.0) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 88, 16, 8);
    if (fabs(val) >= 0.5) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    nvgBeginPath(args.vg);
    nvgRect(args.vg, 0, 99, 16, 8);
    if (fabs(val) > 0.0) {
      nvgFillColor(args.vg, green);
    } else {
      nvgFillColor(args.vg, grey);
    }
    nvgFill(args.vg);

    shadow.draw(args.vg);
  }
};

struct CDSlider : app::SvgSlider {
public:
	CDSlider() {
		Vec margin = Vec(4, 4);
		maxHandlePos = Vec(1.3, -7).plus(margin);
		minHandlePos = Vec(1.3, 76).plus(margin);
    setBackgroundSvg(APP->window->loadSvg(asset::plugin(pluginInstance,"res/CDSlider.svg")));
		background->wrap();
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(2));
    setHandleSvg(APP->window->loadSvg(asset::plugin(pluginInstance,"res/CDSliderHandle.svg")));
		handle->wrap();
  }
};

struct CDLEDBezel : LEDBezel {
private:
  CDShadow shadow = CDShadow();

public:
  void setSVG(std::shared_ptr<SVG> svg) {
    shadow.setBox(box);
  }

  void draw(const DrawArgs &args) override {
    /** shadow */
    shadow.draw(args.vg);

    LEDBezel::draw(args);
  }
};

template <typename BASE>
struct CDButtonLight : BASE {
	CDButtonLight() {
	  this->box.size = mm2px(Vec(6.0, 6.0));
	}
};

/*
bq_type_lowpass = 0,
bq_type_highpass,
bq_type_bandpass,
bq_type_notch,
bq_type_peak,
bq_type_lowshelf,
bq_type_highshelf
*/

struct EqTypeDisplay : TransparentWidget {
  uint8_t *value = nullptr;
  std::shared_ptr<Font> font;

	EqTypeDisplay ( ) {
    value = nullptr;
    font = APP->window->loadFont(asset::plugin(pluginInstance, "res/digit.ttf"));
  }

  void draw (const DrawArgs &args) override {
    nvgFontSize(args.vg, 6);
		nvgFontFaceId(args.vg, font->handle);
		nvgTextLetterSpacing(args.vg, 0.5);

		nvgFillColor(args.vg, nvgRGBA(0x00, 0xff, 0x00, 0xff));

    if (value) {
      switch (*value) {
      case 0:
        nvgText(args.vg, box.pos.x + 12, box.pos.y + 2, "LOW", NULL);
        nvgText(args.vg, box.pos.x + 10, box.pos.y + 10, "PASS", NULL);
        break;
      case 1:
        nvgText(args.vg, box.pos.x + 10, box.pos.y + 2, "HIGH", NULL);
        nvgText(args.vg, box.pos.x + 10, box.pos.y + 10, "PASS", NULL);
        break;
      case 2:
        nvgText(args.vg, box.pos.x + 10, box.pos.y + 2, "BAND", NULL);
        nvgText(args.vg, box.pos.x + 10, box.pos.y + 10, "PASS", NULL);
        break;
      case 3:
        nvgText(args.vg, box.pos.x + 7, box.pos.y + 6, "NOTCH", NULL);;
        break;
      case 4:
        nvgText(args.vg, box.pos.x + 8, box.pos.y + 6, "PEAK", NULL);;
        break;
      case 5:
        nvgText(args.vg, box.pos.x + 12, box.pos.y + 2, "LOW", NULL);
        nvgText(args.vg, box.pos.x + 7, box.pos.y + 10, "SHELF", NULL);
        break;
      case 6:
        nvgText(args.vg, box.pos.x + 10, box.pos.y + 2, "HIGH", NULL);
        nvgText(args.vg, box.pos.x + 7, box.pos.y + 10, "SHELF", NULL);
        break;
      default:
        nvgText(args.vg, box.pos.x + 1, box.pos.y + 1, "ERROR", NULL);
      }
    } else {
      nvgText(args.vg, box.pos.x + 1, box.pos.y + 1, "ERROR", NULL);;
    }

  }
};

struct FrequencyDisplay : TransparentWidget {
  float *value;
  std::shared_ptr<Font> font;

	FrequencyDisplay ( ) {
    value = NULL;
    font = APP->window->loadFont(asset::plugin(pluginInstance, "res/digit.ttf"));
  }

  void draw (const DrawArgs &args) override {
    char text[16];
    nvgFontSize(args.vg, 7);
		nvgFontFaceId(args.vg, font->handle);
		nvgTextLetterSpacing(args.vg, 0.5);

		nvgFillColor(args.vg, nvgRGBA(0x00, 0xff, 0x00, 0xff));

    if (value) {
      sprintf(text, "%5.0fHz", *value);
    } else {
      sprintf(text, "ERROR");
    }

    nvgText(args.vg, box.pos.x + 1, box.pos.y + 1, text, NULL);
  }
};

struct WaveSelect : TransparentWidget {
  uint8_t *value;
  std::shared_ptr<Font> font;

	WaveSelect ( ) {
    value = NULL;
    font = APP->window->loadFont(asset::plugin(pluginInstance, "res/digit.ttf"));
  }

  void draw (const DrawArgs &args) override {
    nvgFontSize(args.vg, 8);
		nvgFontFaceId(args.vg, font->handle);
		nvgTextLetterSpacing(args.vg, 1);

		nvgFillColor(args.vg, nvgRGBA(0x00, 0xff, 0x00, 0xff));

    if (value) {
      switch (*value) {
      case 0:
        nvgText(args.vg, box.pos.x + 1, box.pos.y + 1, "SIN", NULL);
        break;
      case 1:
        nvgText(args.vg, box.pos.x + 1, box.pos.y + 1, "TRI", NULL);
        break;
      case 2:
        nvgText(args.vg, box.pos.x + 1, box.pos.y + 1, "SAW", NULL);
        break;
      case 3:
        nvgText(args.vg, box.pos.x + 1, box.pos.y + 1, "SQR", NULL);
        break;
      default:
        nvgText(args.vg, box.pos.x + 1, box.pos.y + 1, "ERR", NULL);
        break;
      }
    } else {
      nvgText(args.vg, box.pos.x + 1, box.pos.y + 1, "NUL", NULL);
    }
  }
};
