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
  SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
  
  SDL_FreeSurface(surface); 
}

void Image::render(Rect dst)
{
  SDL_Rect dstrect = dst.as_sdl();
  sec(SDL_RenderCopy(renderer, texture, NULL, &dstrect));
}

void Image::render(V2 pos)
{
  render({pos.x, pos.y, src.w, src.h});
}

void Image::render(int x, int y, int w, int h)
{
  render({x, y, w, h});
}

void Image::render(int x, int y)
{
  render((V2) {x, y});
}
