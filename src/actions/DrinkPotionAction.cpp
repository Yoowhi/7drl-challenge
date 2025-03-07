#include "DrinkPotionAction.hpp"

DrinkPotionAction::DrinkPotionAction(Entity* actor, PotionItem* item) : Action(actor, 100), item(item) {}

void DrinkPotionAction::execute() {
    actor->inventory->remove(item);
    actor->being->updateHp(item->hp);
    actor->being->updateStamina(item->stamina);
}
