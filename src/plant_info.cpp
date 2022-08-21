#include "plant_info.hpp"

const std::string plant_paths[PLANT_COUNT] = {
  "assets/carrot.png",
  "assets/radish.png",
  "assets/eggplant.png",
  "assets/lettuce.png",
  "assets/watermelon.png",
  "assets/tomato.png",
  "assets/dragonfruit.png",
  "assets/starfruit.png"
};

const std::string plant_white_paths[PLANT_COUNT] = {
  "assets/white_carrot.png",
  "assets/white_radish.png",
  "assets/white_eggplant.png",
  "assets/white_lettuce.png",
  "assets/white_watermelon.png",
  "assets/white_tomato.png",
  "assets/white_dragonfruit.png",
  "assets/white_starfruit.png"
};

const PlantInfo plant_info[PLANT_COUNT] = {
  [PLANT_CARROT] = {CURRENCY_RABBIT, 0, 0},
  [PLANT_RADISH] = {CURRENCY_RABBIT, 25, 15},
  [PLANT_EGGPLANT] = {CURRENCY_RABBIT, 300, 50},
  [PLANT_LETTUCE] = {CURRENCY_RABBIT, 1000, 100},
  [PLANT_WATERMELON] = {CURRENCY_BEAR, 1, 1},
  [PLANT_TOMATO] = {CURRENCY_BEAR, 1, 1},
  [PLANT_DRAGONFRUIT] = {CURRENCY_BEAR, 5, 2},
  [PLANT_STARFRUIT] = {CURRENCY_RABBIT, 0, 0}
};

// Returns 'Clicks required' subtraction amount
double lettuce_table(int level)
{
  if (level < 45) return 10 - level / 5;
  if (level < 55) return 1.5;
  if (level < 65) return 1;
  if (level < 75) return 0.5;
  if (level <= 100) return 0.2;

  fprintf(stderr, "Unexpected level in lettuce_table! Got %d", level);
  exit(1);
}
