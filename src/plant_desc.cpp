#include "plant.hpp"
#include "util.hpp"

void set_plant_desc(Plant *p)
{
  bool e = p->rstate->config->language == LANGUAGE_EN;
  TextField *f = &p->desc_field;

  switch (p->type) {
  case PLANT_CARROT:
    f->add_text(e ? "Gives %s" : "Даёт %s", format_money(p->reward).c_str());
    f->add_rabbit();
    f->add_text(e ? " per click" : " за клик");
    break;
  case PLANT_RADISH:
    f->add_text(e ? "Gives %s" : "Даёт %s", format_money(p->reward).c_str());
    f->add_rabbit();
    f->add_text(e ? " per second" : " за секунду");
    f->add_line();
    f->add_text(e ? "(LVL %d, Total %s" : "(Уровень %d, Всего %s", p->level, format_money(p->income).c_str());
    f->add_rabbit();
    f->add_text(")");
    break;
  case PLANT_EGGPLANT:
    f->add_text(e ? "Increases " : "Повышает награду ");
    f->add_plant(PLANT_CARROT);
    f->add_text(e ? " reward by 0.1" : " на 0.1");
    f->add_line();
    f->add_text(e ? "(LVL %d, Total +%s)" : "(Уровень %d, Всего +%s)", p->level, format_money(p->reward).c_str());
    break;
  case PLANT_LETTUCE:
    f->add_text(e ? "Every %s" : "Каждые %s", format_money(p->reward).c_str());
    f->add_plant(PLANT_CARROT);
    f->add_text(e ? " clicks give 1" : " кликов дают 1");
    f->add_bear();
    f->add_line();

    if (p->level == 100) {
      f->add_text(e ? "(LVL 100)" : "(Уровень 100)");
    } else {
      f->add_text(e ? "(LVL %d, Next %s)" : "(Уровень %d, Потом %s)", p->level, format_money(lettuce_table(p->level + 1)).c_str());
    }

    break;
  case PLANT_WATERMELON:
    f->add_text(e ? "Increases " : "Повышает награду ");
    f->add_plant(PLANT_RADISH);
    f->add_text(e ? " reward by 10%%%%" : " на 10%%%%");
    f->add_line();
    f->add_text(e ? "(LVL %d, Total +%s%%)" : "(Уровень %d, Всего +%s%%)", p->level, format_money(p->reward).c_str());
    break;
  case PLANT_TOMATO:
    f->add_text(e ? "Increases " : "Повышает награду ");
    f->add_plant(PLANT_EGGPLANT);
    f->add_text(e ? " reward by 10%%%%" : " на 10%%%%");
    f->add_line();
    f->add_text(e ? "(LVL %d, Total +%s%%)" : "(Уровень %d, Всего +%s%%)", p->level, format_money(p->reward).c_str());
    break;
  case PLANT_DRAGONFRUIT:
    f->add_text(e ? "Gives %s" : "Даёт %s", format_money(p->reward, 4).c_str());
    f->add_bear();
    f->add_text(e ? " per second" : " за секунду");
    f->add_line();
    f->add_text(e ? "The amount is entirely based on " : "Сумма полностью зависит от бонуса ");
    f->add_plant(PLANT_LETTUCE);
    if (e) f->add_text(" bonus");
    f->add_line();
    f->add_text(e ? "(LVL %d, Total %s" : "(Уровень %d, Всего %s", p->level, format_money(p->income, 4).c_str());
    f->add_bear();
    f->add_text(")");
    break;
  case PLANT_STARFRUIT:
    // TODO
    break;
  case PLANT_COUNT:
    fprintf(stderr, "ERROR: set_plant_desc: got PLANT_COUNT case");
    exit(1);
    break;
  }
}
