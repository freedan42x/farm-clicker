#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_FontCache.h>
#include "language.hpp"

struct Config
{ 
  Language language;
  bool show_custom_cursor;
  
  int width, height;
  bool fullscreen;
  int fps; 

  int plant_size;
  int plant_hgap, plant_vgap;
  int rows, cols;
  int plants_per_screen;
  int plants_total_width, plants_total_height;
  int plants_start_x, plants_start_y;

  int text_size_pt;
  int text_size_px;
  int text_line_spacing;
  SDL_Color text_color;
  SDL_Color outline_color;

  Config();
  void calculate();
};
