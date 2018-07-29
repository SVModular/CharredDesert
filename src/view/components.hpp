#pragma once

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

  void setSize (float size) {
    CDShadow::size = size;
  }

  void setStrength (float strength) {
    CDShadow::strength = strength;
  }

  void drawShadow (NVGcontext *vg, float strength, float size) {
    // add shadow
    nvgBeginPath(vg);
    nvgRect(vg, -20, -20, box.size.x + 40, box.size.y + 40);

    NVGcolor icol = nvgRGBAf(0.0f, 0.0f, 0.0f, strength);
    NVGcolor ocol = nvgRGBAf(0.0f, 0.0f, 0.0f, 0.f);;

    NVGpaint paint = nvgRadialGradient(vg, box.size.x / 2 + shadowPos.x, box.size.y / 2 + shadowPos.y,
                                       box.size.x * 0.3f, box.size.x * size, icol, ocol);
    nvgFillPaint(vg, paint);
    nvgFill(vg);
  }

  void draw (NVGcontext *vg) {
    drawShadow(vg, strength, size);
  };
};

struct CDKnob : RoundKnob {
protected:
  CDShadow shadow = CDShadow();

public:
  void setSVG (std::shared_ptr<SVG> svg) {
    RoundKnob::setSVG(svg);

    shadow.setBox(box);
  }

  void draw(NVGcontext *vg) override {
    /** shadow */
    shadow.draw(vg);

    /** component */
    FramebufferWidget::draw(vg);
  }
};

struct LightKnob : CDKnob {
  LightKnob ( ) {
    setSVG(SVG::load(assetPlugin(plugin, "res/Knob.svg")));
  }
};

struct LightKnobSnap : LightKnob {
  LightKnobSnap ( ) {
    snap = true;
  }
};

struct CDPort : SVGPort {
private:
  CDShadow shadow = CDShadow();

public:
  CDPort ( ) {
    background->svg = SVG::load(assetPlugin(plugin, "res/Port.svg"));
    background->wrap();
    box.size = background->box.size;

    /** inherit dimensions */
    shadow.setBox(box);
    shadow.setSize(0.4);
    shadow.setShadowPosition(2, 1);
  }

  void draw (NVGcontext *vg) override {
    shadow.draw(vg);
    SVGPort::draw(vg);
  }
};
