#pragma once

#include "text_field.hpp"
#include "plant.hpp"
#include "save_state.hpp"

struct Game
{
  Config *config;

  int cursor_x, cursor_y;

  double money[CURRENCY_COUNT];
  double income[CURRENCY_COUNT]; // per second
  CurrencyType last_currency_unlocked;

  TextField money_field;

  Plant *plants[PLANT_COUNT];
  PlantType cur_plant_hovered; // -1 if none
  PlantType last_plant_unlocked;

  Game(RenderState *rstate);
  void update_fields();
  void update_plant_fields();
  void render_fields();
  void calculate_rewards();
};
