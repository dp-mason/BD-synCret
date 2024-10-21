#pragma once
#include <rack.hpp>
#include "../../extism/runtime/extism.h"
#include <stdio.h>

using namespace rack;

// Declare the Plugin, defined in plugin.cpp
extern Plugin* pluginInstance;

// Declare each Model, defined in each module source file
// extern Model* modelMyModule;

struct TextDisplay : TransparentWidget {
  std::string text = "Use The Menu to set the Wasm Module";
  
  std::shared_ptr<Font> font;

  TextDisplay ( ) {
    font = APP->window->loadFont(asset::plugin(pluginInstance, "res/UbuntuMono-Regular.ttf"));
  }

  void changeText (std::string display_text) {
    this->text = display_text;
  }

  void draw (const DrawArgs &args) override {
    nvgFontSize(args.vg, 16);
    nvgFontFaceId(args.vg, font->handle);
    nvgTextLetterSpacing(args.vg, 1);

    nvgBeginPath(args.vg);
    nvgFillColor(args.vg, nvgRGBA(0xFF, 0xFF, 0xFF, 0xFF));

    nvgText(args.vg, 0, 0, this->text.c_str(), NULL);
  }
};
