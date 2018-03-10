#pragma once

#include "rack.hpp"
#include "asset.hpp"
#include "components.hpp"

extern Plugin *plugin;

struct Jack : SVGPort {
  Jack() {
    background->svg = SVG::load(assetPlugin(plugin, "res/components/Jack.svg"));
    background->wrap();
    box.size = background->box.size;
  }
};

struct Davies1900hRedSnapKnob : Davies1900hRedKnob {
  Davies1900hRedSnapKnob ( ) {
    snap = true;
  }
};

struct MotorWidget : TransparentWidget {
	float diameter;
	float *value;
	bool *connected;

	MotorWidget ( ) { }

	void draw (NVGcontext *vg) {
		if (*connected) {
		  float xx = diameter * sin(-(*value * 0.17 + 0.15) * M_PI) ;
		  float yy = diameter * cos((*value * 0.17 + 0.15) * M_PI) ;

			nvgBeginPath(vg);
			nvgCircle(vg, 0.0f, 0.0f, diameter);
			nvgFillColor(vg, nvgRGBA(0xf3, 0x00, 0x00, 0xff));
			nvgFill(vg);

			nvgStrokeWidth(vg, 1.2f);

			nvgStrokeColor(vg, nvgRGBA(0xff, 0xff, 0xff, 0xff));
			{
				nvgBeginPath(vg);
				nvgMoveTo(vg, 0, 0);
				nvgLineTo(vg, xx, yy);
				nvgClosePath(vg);
			}

			nvgStroke(vg);
		}
	}
};
