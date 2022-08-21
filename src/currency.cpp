#include "currency.hpp"
#include "render_state.hpp"
#include <cassert>

Image *currency2image(RenderState *rstate, CurrencyType type)
{
  switch (type) {
  case CURRENCY_RABBIT:
    return rstate->rabbit_img;
  case CURRENCY_BEAR:
    return rstate->bear_img;
  case CURRENCY_FOX:
    return rstate->fox_img;
  default:
    break;
  }

  assert(0 && "Unreachable (probably)");
}
