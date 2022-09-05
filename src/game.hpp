#pragma once

#include "text_field.hpp"
#include "plant.hpp"
#include "util.hpp"

struct Game
{
  Config *config;

  double money[CURRENCY_COUNT];
  double income[CURRENCY_COUNT]; // per second
  CurrencyType last_currency_unlocked;

  TextField money_field;

  Plant *plants[PLANT_COUNT];
  PlantType last_plant_unlocked;

  uint64_t playtime;
  uint64_t time_since_start;
  uint64_t awaytime;
  
  Game(RenderState *rstate);
  void update_fields();
  void update_plant_fields();
  void render_fields();
  void calculate_rewards();

  void write(Writer<StringBuffer> &w);
  void read(Value &d);
};
