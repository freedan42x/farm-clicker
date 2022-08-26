#include <cassert>
#include "game.hpp"
#include "config.hpp"
#include "interact.hpp"
#include "util.hpp"
#include "plant_desc.hpp"

Plant::Plant(RenderState *rstate, PlantType type) : rstate(rstate),
						    anim_state(rstate->config),
						    type(type),
						    currency_type(plant_info[type].type),
						    income(0.0),
						    price_field(TextField(rstate)),
						    desc_field(TextField(rstate))
{
  assert(rstate);

  x = rstate->config->plants_start_x +
    (rstate->config->plant_size + rstate->config->plant_hgap) *
    (type % rstate->config->plants_per_screen % rstate->config->rows);
  y = rstate->config->plants_start_y +
    (rstate->config->plant_size + rstate->config->plant_vgap) *
    (type % rstate->config->plants_per_screen / rstate->config->rows);
  w = rstate->config->plant_size;
  h = rstate->config->plant_size;
  
  Interaction interaction;
  interaction.type = InteractionType::Plant;
  interaction.x = x;
  interaction.y = y;
  interaction.w = rstate->config->plant_size;
  interaction.h = rstate->config->plant_size;
  interaction.plant_type = type;
  rstate->interactions.push_back(interaction);
}

void Plant::update_fields(PlantType last_plant_unlocked)
{
  price_field.clear();
  desc_field.clear();

  if (last_plant_unlocked + 1 < type) {
    price_field.add_text("???");
    desc_field.add_text("???");
    return;
  }

  if (type == PLANT_LETTUCE && level == 100) {
    price_field.add_text("MAX");
  } else {
    price_field.add_text("%d", price);
    price_field.add_currency(currency_type, true);
  }

  set_plant_desc(this);
}

void Plant::on_click(Game *game)
{
  assert(game);

  double *money = &game->money[currency_type];

  if (type == PLANT_CARROT) {
    *money += reward;

    if (game->plants[PLANT_LETTUCE]->level > 0) {
      clicks++;

      if (clicks >= game->plants[PLANT_LETTUCE]->reward) {
	clicks -= game->plants[PLANT_LETTUCE]->reward;
	game->money[CURRENCY_BEAR]++;
      }
    }
      
    return;
  }

  if (type == PLANT_LETTUCE && level == 100) return;

  if (*money >= price && game->last_plant_unlocked + 1 >= type) {
    if (level == 0) {
      game->last_plant_unlocked = type;
      rstate->plant_imgs[type]->load(plant_paths[type]);

      if (type == PLANT_LETTUCE) {
	game->last_currency_unlocked = CURRENCY_BEAR;
      }
    }

    *money -= price;
    price += plant_info[type].price_growth;
    level++;
  }
}

void Plant::render(bool hovered)
{
  int anim_x = x;
  int anim_y = y;
  int anim_w = w;
  int anim_h = h;
  anim_state.apply(&anim_x, &anim_y, &anim_w, &anim_h);
  rstate->plant_imgs[type]->render(anim_x, anim_y, anim_w, anim_h);

  if (type != PLANT_CARROT) {
    price_field.render(x + (w - price_field.lines[0].width) / 2, y + h + 5);
  }

  if (hovered) {
    desc_field.render(0, rstate->config->height - 100, rstate->config->width);
  }
}
