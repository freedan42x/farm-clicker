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
  AnimState anim_state;

  int x, y, w, h;

  PlantType type;
  CurrencyType currency_type;
  uint64_t price;
  uint64_t level;
  double reward;
  double income; // per second
  double clicks;
  
  TextField price_field;
  TextField desc_field;

  Plant(RenderState *rstate, PlantType type);

  void update_fields(PlantType last_plant_unlocked);
  void on_click(Game *game);
  void render(bool hovered);

  void write(Writer<StringBuffer> &w);
  void read(Value &d);
};
