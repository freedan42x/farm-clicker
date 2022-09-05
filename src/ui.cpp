#include "ui.hpp"

bool Ui::button_hover(Image *image, Rect r)
{
  image->render(r);
  return r.contains(cursor);
}
