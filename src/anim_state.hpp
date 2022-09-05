#pragma once

#include "config.hpp"
#include "linear.hpp"

enum class AnimType
{
  None,
  Expand,
  Shrink
};

struct AnimState
{
  Config *config;

  AnimType type;
  double offset;
  double offset_max;
  double offset_step;

  AnimState(Config *config);
  
  void apply(int *x, int *y, int *w, int *h);
  void apply(Rect *r);
  void step();
  void make_expand(double scale, double duration);
  void make_shrink(double duration);
  void shrink();
};
