#include "render_state.hpp"
#include <SDL2/SDL_image.h>
#include "util.hpp"
#include "config.hpp"

RenderState::RenderState()
{
  sec(SDL_Init(SDL_INIT_VIDEO));
  sec(IMG_Init(IMG_INIT_PNG));

  config = Config();
  config.calculate();
 
  window = sec(SDL_CreateWindow(
		      "Title",
		      SDL_WINDOWPOS_UNDEFINED,
		      SDL_WINDOWPOS_UNDEFINED,
		      config.width,
		      config.height,
		      config.fullscreen ? SDL_WINDOW_FULLSCREEN : 0));

  renderer = sec(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

  SDL_Surface *cursor_surface = sec(IMG_Load("assets/rabbit_cream.png"));

  default_cursor = sec(SDL_GetCursor());
  custom_cursor = sec(SDL_CreateColorCursor(cursor_surface, 0, 0));
  SDL_FreeSurface(cursor_surface);
  SDL_SetCursor(custom_cursor);

  font = FC_CreateFont();
  font_outline = FC_CreateFont();
  FC_LoadFont(font, renderer, "assets/fonts/Retroville NC.ttf", config.text_size_pt, config.text_color, TTF_STYLE_NORMAL);
  FC_LoadFont(font_outline, renderer, "assets/fonts/Retroville NC.ttf", config.text_size_pt, config.outline_color, TTF_STYLE_OUTLINE);
  FC_SetSpacing(font_outline, -2);

  lang = LANG_RU;
  
  for (auto i = 0; i < PLANT_COUNT; i++) {
    plant_imgs[i] = new Image(renderer);
    plant_imgs[i]->load(i == PLANT_CARROT ? plant_paths[i] : plant_white_paths[i]);
  }

  rabbit_img = new Image(renderer);
  rabbit_img->load("assets/rabbit.png");

  bear_img = new Image(renderer);
  bear_img->load("assets/bear.png");
  
  fox_img = new Image(renderer);
  fox_img->load("assets/fox.png");

  paw_img = new Image(renderer);
  paw_img->load("assets/paw.png");
}

RenderState::~RenderState()
{
  FC_FreeFont(font);
  FC_FreeFont(font_outline);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
}

void RenderState::draw_text(int x, int y, const char *msg)
{
  FC_Draw(font_outline, renderer, x, y, msg);
  FC_Draw(font, renderer, x, y, msg);   
}
