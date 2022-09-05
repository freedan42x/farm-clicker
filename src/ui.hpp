#pragma once

#include "image.hpp"

struct Ui
{
  V2 cursor;
  bool clicked;

  bool button_hover(Image *image, Rect r);
};
