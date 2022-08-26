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

uint64_t plant_price_table(PlantType type, int level)
{
  return plant_info[type].initial_price + level * plant_info[type].price_growth;
}

// Returns 'Clicks required'
double lettuce_table(int level)
{
  double k = level - 1;
  return (int) (300.0
		- k
		- pow((int) (k / 1.75), 1.1)
		- pow((int) (k / 2.5), 1.1)
		- pow((int) (k / 3), 1.15));
}
