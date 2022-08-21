#pragma once

#include "plant_info.hpp"

enum class InteractionType
{
  Plant
};

struct Interaction
{
  InteractionType type;
  int x, y, w, h;

  PlantType plant_type; // For InteractionType of Plant

  bool check(const int x, const int y);
};
