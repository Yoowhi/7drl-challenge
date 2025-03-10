#include "PotionItem.hpp"
#include "../actions/DrinkPotionAction.hpp"
#include "libtcod.hpp"
#include "../Being.hpp"

PotionItem::PotionItem(Entity* owner) : Item(owner) {}

Action* PotionItem::use(Entity* user) {
    return new DrinkPotionAction(user, this);
}

std::string PotionItem::getPrintMainStat(Being* being) {
    if (hp > 0 && stamina > 0) {
        return tcod::stringf("HP+%u ST+%u", (int)hp,(int)stamina);
    }
    if (hp > 0) {
        return tcod::stringf("HP+%u", (int)hp);
    } else {
        return tcod::stringf("ST+%u", (int)stamina);
    }
}
