#include "DrinkPotionAction.hpp"
#include "../Entity.hpp"
#include "../Container.hpp"
#include "../items/PotionItem.hpp"
#include "../Being.hpp"
#include "../Engine.hpp"
#include "../GUI.hpp"
#include "../colors.h"

DrinkPotionAction::DrinkPotionAction(Entity* actor, PotionItem* item) : Action(actor, 100), item(item) {}

void DrinkPotionAction::execute() {
    actor->inventory->remove(item);
    actor->being->updateHp(item->hp);
    actor->being->updateStamina(item->stamina);
    actor->being->restoreStats(time);
    engine->gui->message(Color::lightestBlue, tcod::stringf("%s drinks %s", actor->name, item->owner->name));
    delete item->owner;
}
