#pragma once

#include <string>
#include "plant_info.hpp"
#include "image.hpp"
#include "anim_state.hpp"
#include "render_state.hpp"
#include "text_field.hpp"

struct Game;

struct Plant
{
  RenderState *rstate;

  int x, y, w, h;
  
  PlantType type;
  AnimState anim_state;

  CurrencyType currency_type;
  ull_t price;
  ull_t level;
  double reward;
  double income; // per second
  double clicks;
  
  TextField price_field;
  TextField desc_field;

  Plant(RenderState *rstate, PlantType type);

  void update_fields(PlantType last_plant_unlocked);
  void on_click(Game *game);
  void render(bool hovered);
};
