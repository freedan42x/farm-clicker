#include <cassert>
#include "text_field.hpp"
#include "config.hpp"

FieldComponent::FieldComponent(std::string text) : type(ComponentType::Text), text(text) { }
FieldComponent::FieldComponent(CurrencyType type) : type(ComponentType::Currency), currency_type(type) { }
FieldComponent::FieldComponent(PlantType type) : type(ComponentType::Plant), plant_type(type) { }
FieldComponent::FieldComponent(int padding) : type(ComponentType::Padding), width(padding) { }

void FieldComponent::render(RenderState *rstate, const int x, const int y)
{ 
  switch (type) {
  case ComponentType::Text:
    rstate->draw_text(x, y, text.c_str());
    break;
  case ComponentType::Currency:
    currency2image(rstate, currency_type)->render(x, y, rstate->config->text_size_px, rstate->config->text_size_px);
    break;
  case ComponentType::Plant:
    rstate->plant_imgs[plant_type]->render(x, y, rstate->config->text_size_px, rstate->config->text_size_px);
    break;
  case ComponentType::Padding:
    // Literally do nothing, it's just a padding bro!
    break;
  }
}

TextFieldLine::TextFieldLine() : width(0) { }

void TextFieldLine::render(RenderState *rstate, const int x, const int y)
{
  int offset = 0;
  for (auto &component : components) {
    component.render(rstate, x + offset, y);
    offset += component.width;
  }  
}

TextField::TextField(RenderState *rstate) : rstate(rstate)
{
  add_line();
}

void TextField::clear()
{
  lines.clear();
  add_line();
}

void TextField::add_text(const char *fmt, ...)
{
  va_list args, args_copy;
  va_start(args, fmt);
  va_copy(args_copy, args);

  int len = vsnprintf(nullptr, 0, fmt, args);
  assert(len > 0);

  std::string result;
  result.resize(len);
  vsnprintf(&result[0], len + 1, fmt, args_copy);

  va_end(args_copy);
  va_end(args);

  auto component = FieldComponent(result);
  component.width = FC_GetWidth(rstate->font, result.c_str());
  lines[lines.size() - 1].components.push_back(component);
  lines[lines.size() - 1].width += component.width;
}

void TextField::add_currency(CurrencyType type, bool ignore_width)
{
  auto component = FieldComponent(type);
  component.width = rstate->config->text_size_px;
  lines[lines.size() - 1].components.push_back(component);
  if (!ignore_width) lines[lines.size() - 1].width += component.width;
}

void TextField::add_plant(PlantType type)
{
  auto component = FieldComponent(type);
  component.width = rstate->config->text_size_px;
  lines[lines.size() - 1].components.push_back(component);
  lines[lines.size() - 1].width += component.width;
}

void TextField::add_padding(int padding)
{
  auto component = FieldComponent(padding);
  lines[lines.size() - 1].components.push_back(component);
  lines[lines.size() - 1].width += padding;
}

void TextField::add_line()
{
  lines.push_back(TextFieldLine());
}

void TextField::render(const int x, const int y)
{
  int line_count = 0;
  for (auto &line : lines) {
    line.render(rstate, x, y + line_count * (rstate->config->text_size_pt + rstate->config->text_line_spacing));
    line_count++;
  }
}

void TextField::render(const int x, const int y, const int align_w)
{
  int line_count = 0;
  for (auto &line : lines) {
    line.render(rstate, x + (align_w - line.width) / 2, y + line_count * (rstate->config->text_size_pt + rstate->config->text_line_spacing));
    line_count++;
  }
}
