#include "DrinkPotionAction.hpp"
#include "../Entity.hpp"
#include "../Container.hpp"
#include "../items/PotionItem.hpp"
#include "../Being.hpp"

DrinkPotionAction::DrinkPotionAction(Entity* actor, PotionItem* item) : Action(actor, 100), item(item) {}

void DrinkPotionAction::execute() {
    actor->inventory->remove(item);
    actor->being->updateHp(item->hp);
    actor->being->updateStamina(item->stamina);
    actor->being->restoreStamina(time);
    delete item->owner;
}
