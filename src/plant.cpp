#include <cassert>
#include "game.hpp"
#include "config.hpp"
#include "util.hpp"
#include "plant_desc.hpp"

Plant::Plant(RenderState *rstate, PlantType type) : rstate(rstate),
						    anim_state(rstate->config),
						    type(type),
						    currency_type(plant_info[type].type),
						    price(plant_price_table(type, 0)),
						    level(type == PLANT_CARROT),
						    clicks(0.0),
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

  anim_state.shrink();
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
    level++;
    price = plant_price_table(type, level);
  }
}

void Plant::render(Ui &ui, Game *game)
{
  if (type != PLANT_CARROT) {
    price_field.render(x + (w - price_field.lines[0].width) / 2, y + h + 5);
  }
  
  Rect anim = {x, y, w, h};
  anim_state.apply(&anim);
  if (ui.button_hover(rstate->plant_imgs[type], anim)) {
    desc_field.render(0, rstate->config->height - 100, rstate->config->width);
    anim_state.make_expand(1.08, 1.5);

    if (ui.clicked) {
      on_click(game);
      game->calculate_rewards();
      game->update_fields();
      game->update_plant_fields();
    }
  } else {
    anim_state.make_shrink(1.5);
  }
}

void Plant::write(Writer<StringBuffer> &w)
{
  w.Key("level");
  w.Uint64(level);

  w.Key("clicks");
  w.Double(clicks);
}

void Plant::read(Value &d)
{
  if (d.HasMember("level")) {
    level = d["level"].GetUint64();
    price = plant_price_table(type, level);
  }

  if (d.HasMember("clicks")) {
    clicks = d["clicks"].GetDouble();
  }
}
