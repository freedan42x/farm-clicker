#pragma once

#include <SDL2/SDL.h>
#include "SDL_FontCache.hpp"
#include <vector>
#include "interact.hpp"
#include "image.hpp"
#include "config.hpp"
#include "plant_info.hpp"
#include "lang.hpp"

struct RenderState
{
  Config config;

  SDL_Window *window;
  SDL_Renderer *renderer;

  SDL_Cursor *default_cursor;
  SDL_Cursor *custom_cursor;

  FC_Font *font;
  FC_Font *font_outline;

  Lang lang;
  
  Image *plant_imgs[PLANT_COUNT];
  
  Image *rabbit_img;
  Image *bear_img;
  Image *fox_img;
  Image *paw_img;
  
  std::vector<Interaction> interactions;

  RenderState();
  ~RenderState();

  void draw_text(int x, int y, const char *msg);
  void render_hover_info();
};
