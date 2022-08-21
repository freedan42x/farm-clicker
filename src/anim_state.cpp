#include "anim_state.hpp"

#include <algorithm>
#include <cassert>
#include "config.hpp"

AnimState::AnimState()
{
  offset = 0;
  offset_step = 0;
}

AnimState::AnimState(Config *config, double scale, double dur)
{
  offset = config->plant_size * (scale - 1);
  offset_step = (config->plant_size + offset) / (config->fps * dur);
}

void AnimState::apply(int *x, int *y, int *w, int *h)
{
  assert(x);
  assert(y);
  assert(w);
  assert(h);

  *x -= offset;
  *y -= offset;
  *w += offset;
  *h += offset;
}

void AnimState::step()
{
  if (offset > 0) {
    offset = std::max(0.0, offset - offset_step);
  }
}
