#include <cassert>
#include "image.hpp"
#include "util.hpp"

Image::Image(SDL_Renderer *renderer) : renderer(renderer) { }

Image::~Image()
{
  assert(texture);
  SDL_DestroyTexture(texture);
}

void Image::load(std::string path)
{
  SDL_Surface *surface = isec(IMG_Load(path.c_str()));
  texture = sec(SDL_CreateTextureFromSurface(renderer, surface));
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  
  SDL_FreeSurface(surface); 
}

void Image::render(const int x, const int y, const int w, const int h)
{
  SDL_Rect dstrect = {x, y, w, h};
  sec(SDL_RenderCopy(renderer, texture, NULL, &dstrect));
}

void Image::render(const int x, const int y)
{
  render(x, y, w, h);
}
