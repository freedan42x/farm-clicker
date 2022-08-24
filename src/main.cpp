#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "render_state.hpp"
#include "util.hpp"
#include "config.hpp"
#include "image.hpp"
#include "plant.hpp"
#include "text_field.hpp"
#include "game.hpp"

int main()
{
  RenderState rstate;
  Image bg(rstate.renderer);
  bg.load("assets/flowers.png");

  Game game(&rstate);
  game.calculate_rewards();
  game.update_fields();
  game.update_plant_fields();

  int frame = 1;
  bool quit = false;
  while (!quit) {
    Uint64 start = SDL_GetPerformanceCounter();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT: {
        quit = true;
      } break;
      case SDL_MOUSEBUTTONDOWN: {
	SDL_GetMouseState(&game.cursor_x, &game.cursor_y);
	for (auto &inter : rstate.interactions) {
	  if (inter.check(game.cursor_x, game.cursor_y)) {
	    switch (inter.type) {
	    case InteractionType::Plant: {
	      Plant *plant = game.plants[inter.plant_type];
	      plant->on_click(&game);
	      game.calculate_rewards();
	      game.update_fields();
	      game.update_plant_fields();
	    } break;
	    }

	    break;
	  }
	}
      } break;
      case SDL_MOUSEMOTION: {
	game.cur_plant_hovered = (PlantType) -1;

	SDL_GetMouseState(&game.cursor_x, &game.cursor_y);
	for (auto &inter : rstate.interactions) {
	  if (inter.check(game.cursor_x, game.cursor_y)) { 
	    switch (inter.type) {
	    case InteractionType::Plant: {
	      game.cur_plant_hovered = inter.plant_type;
	    } break;
	    }
	    break;
	  }
	}
      } break;
      default:
	break;
      }
    }

    if (frame > rstate.config.fps) {
      frame = 0;

      for (auto i = 0; i < CURRENCY_COUNT; i++) {
	game.money[i] += game.income[i];
      }

      game.update_fields();
    }

    SDL_RenderClear(rstate.renderer);

    bg.render(0, 0, rstate.config.width, rstate.config.height);

    for (auto &plant : game.plants) {
      plant->anim_state.step();
      plant->render(game.cur_plant_hovered == plant->type);  
    }

    game.render_fields();
    
    SDL_Rect rect = {10, 10, rstate.config.text_size_px * 2, rstate.config.text_size_px * 2};
    SDL_RenderCopy(rstate.renderer, rstate.paw_img->texture, nullptr, &rect);

    SDL_RenderPresent(rstate.renderer);

    frame++;
    
    float elapsed = (SDL_GetPerformanceCounter() - start) / (float) SDL_GetPerformanceFrequency();
    SDL_Delay(floor(1000.0f / rstate.config.fps - elapsed));
  }

  return 0;
}