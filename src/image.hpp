#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "linear.hpp"

struct Image
{
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  Rect src;

  Image(SDL_Renderer *renderer);
  ~Image();

  void load(std::string path);
  void render(Rect dst);
  void render(V2 pos);
  void render(int x, int y, int w, int h);
  void render(int x, int y);
};
