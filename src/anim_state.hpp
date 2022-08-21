#pragma once

#include "config.hpp"

struct AnimState
{
  Config *config;
  
  double offset;
  double offset_step;

  AnimState();
  AnimState(Config *config, double scale, double dur);
  
  void apply(int *x, int *y, int *w, int *h);
  void step();
};
