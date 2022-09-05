#pragma once

#include <SDL2/SDL.h>

struct V2
{
  int x, y;
};

struct Rect
{
  int x, y, w, h;

  SDL_Rect as_sdl();
  bool contains(V2 pos);
};
