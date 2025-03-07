#include "libtcod.hpp"
#include "../Controller.hpp"
#include "../Action.hpp"
#include "../Entity.hpp"
#include "../Equipment.hpp"
#include "../Being.hpp"
#include "../Map.hpp"
#include "../ActionQueue.hpp"
#include "../Engine.hpp"
#include "../items/PotionItem.hpp"
#include "../Container.hpp"
#include "DrinkPotionAction.hpp"

DrinkPotionAction::DrinkPotionAction(Entity* actor, PotionItem* item) : Action(actor, 100), item(item) {}

void DrinkPotionAction::execute() {
    actor->inventory->remove(item);
    actor->being->updateHp(item->hp);
    actor->being->updateStamina(item->stamina);
}
