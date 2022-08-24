#include <cassert>
#include "game.hpp"
#include "config.hpp"
#include "util.hpp"

Game::Game(RenderState *rstate) : money_field(TextField(rstate))
{
  config = rstate->config;

  SDL_GetMouseState(&cursor_x, &cursor_y);

  for (auto i = 0; i < PLANT_COUNT; i++) {
    plants[i] = new Plant(rstate, (PlantType) i);
  }
  cur_plant_hovered = (PlantType) -1;
}

void Game::update_fields()
{
  money_field.clear();
  for (auto i = 0; i <= last_currency_unlocked; i++) {
    if (i != 0) money_field.add_padding(15);

    if (money[i] > 100) {
      money_field.add_text("%llu", (ull_t) money[i]);
    } else {
      money_field.add_text("%s", format_money(money[i]).c_str());
    }

    money_field.add_currency((CurrencyType) i);
  }
}

void Game::update_plant_fields()
{
  for (auto &plant : plants) {
    plant->update_fields(last_plant_unlocked);
  }
}

void Game::render_fields()
{
  money_field.render(config->plants_start_x, 15);
}

void Game::calculate_rewards()
{
  plants[PLANT_TOMATO]->reward = plants[PLANT_TOMATO]->level * 10;
  plants[PLANT_EGGPLANT]->reward = apply_percent(plants[PLANT_EGGPLANT]->level / 10.0, plants[PLANT_TOMATO]->reward);
  plants[PLANT_CARROT]->reward = plants[PLANT_CARROT]->level + plants[PLANT_EGGPLANT]->reward;

  plants[PLANT_WATERMELON]->reward = plants[PLANT_WATERMELON]->level * 10;
  plants[PLANT_RADISH]->reward = apply_percent(0.1, plants[PLANT_WATERMELON]->reward);
  plants[PLANT_RADISH]->income = plants[PLANT_RADISH]->level * plants[PLANT_RADISH]->reward;

  plants[PLANT_DRAGONFRUIT]->reward = plants[PLANT_LETTUCE]->level > 0 ? 1.0 / plants[PLANT_LETTUCE]->reward : 0;
  plants[PLANT_DRAGONFRUIT]->income = plants[PLANT_DRAGONFRUIT]->level * plants[PLANT_DRAGONFRUIT]->reward;

  income[CURRENCY_RABBIT] = plants[PLANT_RADISH]->income;
  income[CURRENCY_BEAR] = plants[PLANT_DRAGONFRUIT]->income;
}
