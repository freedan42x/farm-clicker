#include "game.hpp"

// This code contains A LOT of code duplication. I'm not sure what to do about it :<

Config_SaveState::Config_SaveState()
{
  language = LANGUAGE_EN;
  show_custom_cursor = true;
  fullscreen = true;
  width = 1366;
  height = 768;
  fps = 60;
}

Config_SaveState::Config_SaveState(Config &config)
{
  language = config.language;
  show_custom_cursor = config.show_custom_cursor;
  fullscreen = config.fullscreen;
  width = config.width;
  height = config.height;
  fps = config.fps;
}

void Config_SaveState::dump(Config *config)
{
  config->language = language;
  config->show_custom_cursor = show_custom_cursor;
  config->fullscreen = fullscreen;
  config->width = width;
  config->height = height;
  config->fps = fps;
}

void Config_SaveState::write(Writer<StringBuffer> &w)
{
  w.Key("language");
  w.Int(language);

  w.Key("show_custom_cursor");
  w.Bool(show_custom_cursor);

  w.Key("fullscreen");
  w.Bool(fullscreen);
  
  w.Key("width");
  w.Int(width);

  w.Key("height");
  w.Int(height);

  w.Key("fps");
  w.Int(fps);
}

void Config_SaveState::read(Value &d)
{
  if (d.HasMember("language")) {
    language = (Language) d["language"].GetInt();
  }

  if (d.HasMember("show_custom_cursor")) {
    show_custom_cursor = d["show_custom_cursor"].GetBool();
  }

  if (d.HasMember("fullscreen")) {
    fullscreen = d["fullscreen"].GetBool();
  }

  if (d.HasMember("width")) {
    width = d["width"].GetInt();
  }

  if (d.HasMember("height")) {
    height = d["height"].GetInt();
  }

  if (d.HasMember("fps")) {
    fps = d["fps"].GetInt();
  }
}

Plant_SaveState::Plant_SaveState(PlantType type)
{
  level = type == PLANT_CARROT;
  clicks = 0.0;
}

Plant_SaveState::Plant_SaveState(Plant &plant)
{
  level = plant.level;
  clicks = plant.clicks;
}

void Plant_SaveState::dump(Plant *plant)
{
  plant->level = level;
  plant->clicks = clicks;
}

void Plant_SaveState::write(Writer<StringBuffer> &w)
{
  w.Key("level");
  w.Uint64(level);

  w.Key("clicks");
  w.Double(clicks);
}

void Plant_SaveState::read(Value &d)
{
  if (d.HasMember("level")) {
    level = d["level"].GetUint64();
  }

  if (d.HasMember("clicks")) {
    clicks = d["clicks"].GetDouble();
  }
}

Game_SaveState::Game_SaveState()
{
  for (auto i = 0; i < CURRENCY_COUNT; i++) {
    money[i] = 1000000.0;
  }
  last_currency_unlocked = CURRENCY_RABBIT;

  for (auto i = 0; i < PLANT_COUNT; i++) {
    plants[i] = new Plant_SaveState((PlantType) i);
  }
  last_plant_unlocked = PLANT_CARROT;
}

Game_SaveState::Game_SaveState(Game &game)
{
  for (auto i = 0; i < CURRENCY_COUNT; i++) {
    money[i] = game.money[i];
  }
  last_currency_unlocked = game.last_currency_unlocked;

  for (auto i = 0; i < PLANT_COUNT; i++) {
    plants[i] = new Plant_SaveState(*game.plants[i]);
  }
  last_plant_unlocked = game.last_plant_unlocked;
}

void Game_SaveState::dump(Game *game)
{
  for (auto i = 0; i < CURRENCY_COUNT; i++) {
    game->money[i] = money[i];
  }
  game->last_currency_unlocked = last_currency_unlocked;

  for (auto i = 0; i < PLANT_COUNT; i++) {
    plants[i]->dump(game->plants[i]);
  }
  game->last_plant_unlocked = last_plant_unlocked;
}

void Game_SaveState::write(Writer<StringBuffer> &w)
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
}

void Game_SaveState::read(Value &d)
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
}

SaveState::SaveState()
{
  this->config = Config_SaveState();
  this->game = Game_SaveState();
}

SaveState::SaveState(Game &game)
{
  this->config = Config_SaveState(*game.config);
  this->game = Game_SaveState(game);
}

void SaveState::write(std::string path)
{
  StringBuffer sbuf;
  Writer<StringBuffer> w(sbuf);

  w.StartObject();
  {
    w.Key("config");
    w.StartObject();
    config.write(w);
    w.EndObject();

    w.Key("game");
    w.StartObject();
    game.write(w);
    w.EndObject();
  }
  w.EndObject();

  FILE *f = fopen(path.c_str(), "w");
  if (f == NULL) {
    fprintf(stderr, "Oopsie-doopsie! Could not open save file `%s`: %s\n", path.c_str(), strerror(errno));
    return;
  }

  if (fwrite(sbuf.GetString(), sbuf.GetLength(), 1, f) != 1) {
    fprintf(stderr, "Oopsie-doopsie! Could not write to save file `%s`: %s\n", path.c_str(), strerror(errno));
    fclose(f);
    return;
  }

  fclose(f);
}

void SaveState::read(std::string path)
{
  FILE *f = fopen(path.c_str(), "r");
  if (f == NULL) {
    printf("NOTE: Could not open save file `%s`: %s\n", path.c_str(), strerror(errno));
    printf("NOTE: Creating new save file `%s`\n", path.c_str());
    return;
  }

  fseek(f, 0, SEEK_END);
  size_t fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *buf = (char *) malloc(fsize + 1);
  if (fread((void *) buf, fsize, 1, f) != 1) {
    fprintf(stderr, "Could not read save file `%s`: %s\n", path.c_str(), strerror(errno));
    fclose(f);
    return;
  }
  buf[fsize] = 0;

  fclose(f);

  Document d;
  if (d.Parse(buf).HasParseError()) {
    fprintf(stderr, "Corrupted save file `%s`\n", path.c_str());
    return;
  }

  if (d.HasMember("config")) {
    config.read(d["config"]);
  }

  if (d.HasMember("game")) {
    game.read(d["game"]);
  }
}
