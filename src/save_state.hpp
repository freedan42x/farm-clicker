#pragma once

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "language.hpp"
#include "currency.hpp"
#include "plant_info.hpp"

struct Config;
struct Plant;
struct Game;

using namespace rapidjson;

struct Config_SaveState
{
  Language language;
  bool show_custom_cursor;
  bool fullscreen;
  int width, height;
  int fps;

  Config_SaveState();
  Config_SaveState(Config &config);
  void dump(Config *config);
  void write(Writer<StringBuffer> &w);
  void read(Value &d);
};

struct Plant_SaveState
{
  uint64_t price;
  uint64_t level;
  double reward;
  double clicks;

  Plant_SaveState(PlantType type);
  Plant_SaveState(Plant &plant);
  void dump(Plant *plant);
  void write(Writer<StringBuffer> &w);
  void read(Value &d);
};

struct Game_SaveState
{
  double money[CURRENCY_COUNT];
  CurrencyType last_currency_unlocked;
  Plant_SaveState *plants[PLANT_COUNT];
  PlantType last_plant_unlocked;

  Game_SaveState();
  Game_SaveState(Game &game);
  void dump(Game *game);
  void write(Writer<StringBuffer> &w);
  void read(Value &d);
};

struct SaveState
{
  Config_SaveState config;
  Game_SaveState game;

  SaveState();
  SaveState(Game &game);
  void write(std::string path);
  void read(std::string path);
};
