#include "linear.hpp"

SDL_Rect Rect::as_sdl()
{
  return {x, y, w, h};
}

bool Rect::contains(V2 pos)
{
  return pos.x >= x && pos.x < x + w
      && pos.y >= y && pos.y < y + h;
}
