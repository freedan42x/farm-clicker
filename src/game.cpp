#include <cassert>
#include "game.hpp"
#include "config.hpp"
#include "util.hpp"

Game::Game(RenderState *rstate) : money_field(TextField(rstate))
{
  config = rstate->config;

  SDL_GetMouseState(&cursor_x, &cursor_y);

  for (auto i = 0; i < CURRENCY_COUNT; i++) {
    money[i] = 0.0;
  }
  last_currency_unlocked = CURRENCY_RABBIT;
  
  for (auto i = 0; i < PLANT_COUNT; i++) {
    plants[i] = new Plant(rstate, (PlantType) i);
  }
  last_plant_unlocked = PLANT_CARROT;
  cur_plant_hovered = (PlantType) -1;
}

void Game::update_fields()
{
  money_field.clear();
  for (auto i = 0; i <= last_currency_unlocked; i++) {
    if (i != 0) money_field.add_padding(15);

    if (money[i] > 100) {
      money_field.add_text("%lu", (uint64_t) money[i]);
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

  plants[PLANT_LETTUCE]->reward = plants[PLANT_LETTUCE]->level > 0 ? lettuce_table(plants[PLANT_LETTUCE]->level) : 0;
  plants[PLANT_DRAGONFRUIT]->reward = plants[PLANT_LETTUCE]->level > 0 ? 1.0 / plants[PLANT_LETTUCE]->reward : 0;
  plants[PLANT_DRAGONFRUIT]->income = plants[PLANT_DRAGONFRUIT]->level * plants[PLANT_DRAGONFRUIT]->reward;

  income[CURRENCY_RABBIT] = plants[PLANT_RADISH]->income;
  income[CURRENCY_BEAR] = plants[PLANT_DRAGONFRUIT]->income;
}

void Game::write(Writer<StringBuffer> &w)
{
  w.Key("money");
  w.StartArray();
  for (auto i = 0; i < CURRENCY_COUNT; i++) {
    w.Double(money[i]);
  }
  w.EndArray();

  w.Key("last_currency_unlocked");
  w.Int(last_currency_unlocked);

  w.Key("plants");
  w.StartArray();
  for (auto i = 0; i < PLANT_COUNT; i++) {
    w.StartObject();
    plants[i]->write(w);
    w.EndObject();
  }
  w.EndArray();

  w.Key("last_plant_unlocked");
  w.Int(last_plant_unlocked);

  // uint64_t cur_time = time(nullptr);
  // if (time_since_start > cur_time) {
  //   printf("Cur time: %lu | Time since start: %lu\n", cur_time, time_since_start);
  //   printf("Are you... from the past?! It's so coooool~ sunuvabitch!\n");
  //   w.Key("playtime");
  //   w.Uint64(playtime);
  // } else {
  //   uint64_t time_diff = cur_time - time_since_start;
  //   w.Key("playtime");
  //   w.Uint64(playtime + time_diff);
  // }

  // w.Key("last_time_played");
  // w.Uint64(cur_time);
}

void Game::read(Value &d)
{
  if (d.HasMember("money")) {
    auto i = 0;
    for (auto &v : d["money"].GetArray()) {
      if (i >= CURRENCY_COUNT) break;

      money[i] = v.GetDouble();
      i++;
    }
  }

  if (d.HasMember("last_currency_unlocked")) {
    last_currency_unlocked = (CurrencyType) d["last_currency_unlocked"].GetInt();
  }

  if (d.HasMember("plants")) {
    auto i = 0;
    for (auto &v : d["plants"].GetArray()) {
      if (i >= PLANT_COUNT) break;

      plants[i]->read(v);
      i++;
    }    
  }

  if (d.HasMember("last_plant_unlocked")) {
    last_plant_unlocked = (PlantType) d["last_plant_unlocked"].GetInt();
  }

  // if (d.HasMember("playtime")) {
  //   playtime = d["playtime"].GetUint64();
  // }

  // if (d.HasMember("last_time_played")) {
  //   last_time_played = d["last_time_played"].GetUint64();
  // }
}
