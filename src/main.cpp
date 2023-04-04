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
#include "ui.hpp"

int main()
{
  std::string save_path = "save1.json";
  
  Document d;
  bool success = read_json(save_path, &d);

  Config config;
  
  if (success && d.HasMember("config")) {
    config.read(d["config"]);
  }
  config.calculate();

  RenderState rstate(&config);
  Game game(&rstate);
  
  if (success && d.HasMember("game")) {
    game.read(d["game"]);
  }

  game.calculate_rewards();
  game.update_fields();
  game.update_plant_fields();

  for (auto i = 0; i < PLANT_COUNT; i++) {
    rstate.plant_imgs[i]->load(game.plants[i]->level > 0 ? plant_paths[i] : plant_white_paths[i]);
  }
  
  printf("Time away: %lu\n", game.awaytime);
  printf("Playtime: %lu\n", game.playtime);

  Ui ui;
  
  Image bg(rstate.renderer);
  bg.load("assets/bg/0.png");

  int frame = 1;
  bool quit = false;
  while (!quit) {
    Uint64 start = SDL_GetPerformanceCounter();

    ui.clicked = false;
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT: {
	write_json(save_path, game);
        quit = true;
      } break;
      case SDL_MOUSEBUTTONDOWN: {
	SDL_GetMouseState(&ui.cursor.x, &ui.cursor.y);
	ui.clicked = true;
      } break;
      case SDL_MOUSEMOTION: {
	SDL_GetMouseState(&ui.cursor.x, &ui.cursor.y);
      } break;
      default:
	break;
      }
    }

    if (frame > config.fps) {
      frame = 0;

      for (auto i = 0; i < CURRENCY_COUNT; i++) {
	game.money[i] += game.income[i];
      }

      game.update_fields();
    }

    SDL_RenderClear(rstate.renderer);

    bg.render(0, 0, config.width, config.height);

    for (auto &plant : game.plants) {
      plant->anim_state.step();
      plant->render(ui, &game);
    }

    game.render_fields();

    SDL_Rect rect = {10, 10, config.text_size_px * 2, config.text_size_px * 2};
    SDL_RenderCopy(rstate.renderer, rstate.paw_img->texture, nullptr, &rect);

    SDL_RenderPresent(rstate.renderer);

    frame++;
    
    float elapsed = (SDL_GetPerformanceCounter() - start) / (float) SDL_GetPerformanceFrequency();
    SDL_Delay(floor(1000.0f / config.fps - elapsed));
  }

  return 0;
}
