#pragma once

#include "rack.hpp"
#include "asset.hpp"

extern Plugin *plugin;

struct Jack : SVGPort {
        Jack() {
                background->svg = SVG::load(assetPlugin(plugin, "res/components/Jack.svg"));
                background->wrap();
                box.size = background->box.size;
        }
};
