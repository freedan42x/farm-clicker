#include "interact.hpp"

bool Interaction::check(const int x, const int y)
{
  return x >= this->x && x < this->x + w
      && y >= this->y && y < this->y + h;
}
