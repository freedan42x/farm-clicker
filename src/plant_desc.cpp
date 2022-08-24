#include "plant.hpp"
#include "util.hpp"

void set_plant_desc_RU(Plant *p)
{ 
  TextField *f = &p->desc_field;

  switch (p->type) {
  case PLANT_CARROT:
    f->add_text("Даёт %s", format_money(p->reward).c_str());
    f->add_rabbit();
    f->add_text(" за клик");
    break;
  case PLANT_RADISH:
    f->add_text("Даёт %s", format_money(p->reward).c_str());
    f->add_rabbit();
    f->add_text(" за секунду");
    f->add_line();
    f->add_text("(Уровень %d, Всего %s", p->level, format_money(p->income).c_str());
    f->add_rabbit();
    f->add_text(")");
    break;
  case PLANT_EGGPLANT:
    f->add_text("Повышает награду ");
    f->add_plant(PLANT_CARROT);
    f->add_text(" на 0.1");
    f->add_line();
    f->add_text("(Уровень %d, Всего +%s)", p->level, format_money(p->reward).c_str());
    break;
  case PLANT_LETTUCE:
    f->add_text("Каждые %s", format_money(p->reward).c_str());
    f->add_plant(PLANT_CARROT);
    f->add_text(" кликов дают 1");
    f->add_bear();
    f->add_line();

    if (p->level == 0) {
      f->add_text("(Уровень 0, Потом 300)");
    } else if (p->level == 100) {
      f->add_text("(Уровень 100)");
    } else {
      f->add_text("(Уровень %d, Потом %s)", p->level, format_money(p->reward - lettuce_table(p->level)).c_str());
    }

    break;
  case PLANT_WATERMELON:
    f->add_text("Повышает награду ");
    f->add_plant(PLANT_RADISH);
    f->add_text(" на 10%%%%");
    f->add_line();
    f->add_text("(Уровень %d, Всего +%s%%)", p->level, format_money(p->reward).c_str());
    break;
  case PLANT_TOMATO:
    f->add_text("Повышает награду ");
    f->add_plant(PLANT_EGGPLANT);
    f->add_text(" на 10%%%%");
    f->add_line();
    f->add_text("(Уровень %d, Всего +%s%%)", p->level, format_money(p->reward).c_str());
    break;
  case PLANT_DRAGONFRUIT:
    f->add_text("Даёт %s", format_money(p->reward, 4).c_str());
    f->add_bear();
    f->add_text(" за секунду");
    f->add_line();
    f->add_text("Сумма полностью зависит от бонуса ");
    f->add_plant(PLANT_LETTUCE);
    f->add_line();
    f->add_text("(Уровень %d, Всего %s", p->level, format_money(p->income, 4).c_str());
    f->add_bear();
    f->add_text(")");
    break;
  case PLANT_STARFRUIT:
    // TODO
    break;
  case PLANT_COUNT:
    fprintf(stderr, "ERROR: set_plant_desc_ru: got PLANT_COUNT case");
    exit(1);
    break;
  }
}

void set_plant_desc_EN(Plant *p)
{ 
  TextField *f = &p->desc_field;

  switch (p->type) {
  case PLANT_CARROT:
    f->add_text("Gives %s", format_money(p->reward).c_str());
    f->add_rabbit();
    f->add_text(" per click");
    break;
  case PLANT_RADISH:
    f->add_text("Gives %s", format_money(p->reward).c_str());
    f->add_rabbit();
    f->add_text(" per second");
    f->add_line();
    f->add_text("(LVL %d, Total %s", p->level, format_money(p->income).c_str());
    f->add_rabbit();
    f->add_text(")");
    break;
  case PLANT_EGGPLANT:
    f->add_text("Increases ");
    f->add_plant(PLANT_CARROT);
    f->add_text(" reward by 0.1");
    f->add_line();
    f->add_text("(LVL %d, Total +%s)", p->level, format_money(p->reward).c_str());
    break;
  case PLANT_LETTUCE:
    f->add_text("Every %s", format_money(p->reward).c_str());
    f->add_plant(PLANT_CARROT);
    f->add_text(" clicks give 1");
    f->add_bear();
    f->add_line();

    if (p->level == 0) {
      f->add_text("(LVL 0, Next 300)");
    } else if (p->level == 100) {
      f->add_text("(LVL 100)");
    } else {
      f->add_text("(LVL %d, Next %s)", p->level, format_money(p->reward - lettuce_table(p->level)).c_str());
    }

    break;
  case PLANT_WATERMELON:
    // Not sure how the fuck this % shit works but it won't work with just one pair of %
    f->add_text("Increases ");
    f->add_plant(PLANT_RADISH);
    f->add_text(" reward by 10%%%%");
    f->add_line();
    f->add_text("(LVL %d, Total +%s%%)", p->level, format_money(p->reward).c_str());
    break;
  case PLANT_TOMATO:
    f->add_text("Increases ");
    f->add_plant(PLANT_EGGPLANT);
    f->add_text(" reward by 10%%%%");
    f->add_line();
    f->add_text("(LVL %d, Total +%s%%)", p->level, format_money(p->reward).c_str());
    break;
  case PLANT_DRAGONFRUIT:
    f->add_text("Gives %s", format_money(p->reward, 4).c_str());
    f->add_bear();
    f->add_text(" per second");
    f->add_line();
    f->add_text("The amount is entirely based on ");
    f->add_plant(PLANT_LETTUCE);
    f->add_text(" bonus");
    f->add_line();
    f->add_text("(LVL %d, Total %s", p->level, format_money(p->income, 4).c_str());
    f->add_bear();
    f->add_text(")");
    break;
  case PLANT_STARFRUIT:
    // TODO
    break;
  case PLANT_COUNT:
    fprintf(stderr, "ERROR: set_plant_desc_en: got PLANT_COUNT case");
    exit(1);
    break;
  }
}

void set_plant_desc(Plant *plant)
{
  switch (plant->rstate->config->language) {
  case LANGUAGE_EN:
    set_plant_desc_EN(plant);
    break;
  case LANGUAGE_RU:
    set_plant_desc_RU(plant);
    break;
  }
}
