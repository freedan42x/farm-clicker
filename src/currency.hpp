#pragma once

#include "image.hpp"

struct RenderState; // Forward declare this motherflipper

typedef unsigned long long ull_t;

enum CurrencyType
{
  CURRENCY_RABBIT,
  CURRENCY_BEAR,
  CURRENCY_FOX,

  CURRENCY_COUNT
};

Image *currency2image(RenderState *rstate, CurrencyType type);
