#pragma once

#include <SDL2/SDL.h>
#include <string>

struct Image
{
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  int x, y, w, h;

  Image(SDL_Renderer *renderer);
  ~Image();

  void load(std::string path);
  void render(const int x, const int y, const int w, const int h);
  void render(const int x, const int y);
};
