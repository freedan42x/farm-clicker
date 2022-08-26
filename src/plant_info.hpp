#pragma once

#include "currency.hpp"

enum PlantType
{
  PLANT_CARROT = 0,
  PLANT_RADISH,
  PLANT_EGGPLANT,
  PLANT_LETTUCE,
  PLANT_WATERMELON,
  PLANT_TOMATO,
  PLANT_DRAGONFRUIT,
  PLANT_STARFRUIT,

  PLANT_COUNT
};

struct PlantInfo
{
  CurrencyType type;
  uint64_t initial_price;
  uint64_t price_growth;
};

extern const std::string plant_paths[PLANT_COUNT];
extern const std::string plant_white_paths[PLANT_COUNT];
extern const PlantInfo plant_info[PLANT_COUNT];

double lettuce_table(int level);
