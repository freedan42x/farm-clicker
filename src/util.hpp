#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <rapidjson/document.h>

// Generic Error Checker
template <typename T>
T *gec(T *result, const char *get_error(void))
{
  if (result == nullptr) {
    fprintf(stderr, "ERROR: %s\n", get_error());
    abort();
  }
  return result;
}

// SDL Error Checker
template <typename T>
T *sec(T *result)
{
  return gec(result, SDL_GetError);
}

// IMG SDL Error Checker
template <typename T>
T *isec(T *result)
{
  return gec(result, IMG_GetError);
}

void sec(int result);
void isec(int result);

std::string format_money(double money, unsigned short prec = 2);

double apply_percent(double x, unsigned short ps);

struct Game;

bool read_json(std::string path, rapidjson::Document *d);
void write_json(std::string path, Game &game);
