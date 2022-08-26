#include "anim_state.hpp"

#include <algorithm>
#include "config.hpp"

AnimState::AnimState(Config *config) : config(config), type(AnimType::None) { }

void AnimState::apply(int *x, int *y, int *w, int *h)
{
  if (type == AnimType::None) return;

  *x -= offset;
  *y -= offset;
  *w += 2 * offset;
  *h += 2 * offset;
}

void AnimState::step()
{
  switch (type) {
  case AnimType::None:
    break;
  case AnimType::Expand:
    offset = std::min(offset_max, offset + offset_step);
    break;
  case AnimType::Shrink:
    offset -= offset_step;
    if (offset <= 0) {
      offset = 0;
      type = AnimType::None;
    }
    break;
  }
}

void AnimState::make_expand(double scale, double duration)
{
  if (type == AnimType::Expand) return;
  
  type = AnimType::Expand;
  offset = 0;
  offset_max = config->plant_size * scale - config->plant_size;
  offset_step = (config->plant_size + offset_max) / (config->fps * duration);
}

void AnimState::make_shrink(double duration)
{
  type = AnimType::Shrink;
  offset_step = (config->plant_size + offset_max) / (config->fps * duration);
}

void AnimState::shrink()
{
  offset = -offset_step;
}
