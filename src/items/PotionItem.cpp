#include "PotionItem.hpp"
#include "../actions/DrinkPotionAction.hpp"

PotionItem::PotionItem(Entity* owner) : Item(owner) {}

Action* PotionItem::use(Entity* user) {
    return new DrinkPotionAction(user, this);
}
