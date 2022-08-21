#pragma once

#include <string>
#include <vector>
#include "render_state.hpp"
#include "currency.hpp"
#include "plant_info.hpp"

enum class ComponentType
{
  Text,
  Currency,
  Plant,
  Padding
};

struct FieldComponent
{
  ComponentType type;
  std::string text;           // For ComponentType of Text
  CurrencyType currency_type; // For ComponentType of Currency
  PlantType plant_type;       // For ComponentType of Plant
  int width;

  FieldComponent(std::string text);
  FieldComponent(CurrencyType type);
  FieldComponent(PlantType type);
  FieldComponent(int padding);

  void render(RenderState *rstate, const int x, const int y);
};

struct TextFieldLine
{
  std::vector<FieldComponent> components;
  int width;

  TextFieldLine();

  void render(RenderState *rstate, const int x, const int y);
};

struct TextField
{
  RenderState *rstate;
  std::vector<TextFieldLine> lines;
  
  TextField(RenderState *rstate);

  void clear();
  void add_text(const char *fmt, ...);
  void add_currency(CurrencyType type, bool ignore_width = false);
  void add_plant(PlantType type);
  void add_padding(int padding);
  void add_line();
  void render(const int x, const int y);
  void render(const int x, const int y, const int align_w);
};

#define add_rabbit() add_currency(CURRENCY_RABBIT)
#define add_bear() add_currency(CURRENCY_BEAR)
#define add_fox() add_currency(CURRENCY_FOX)
