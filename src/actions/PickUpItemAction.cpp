#include "PickUpItemAction.hpp"
#include "libtcod.hpp"
#include "../Engine.hpp"
#include "../Entity.hpp"
#include "../Container.hpp"
#include "../Map.hpp"
#include "../Being.hpp"
#include "../GUI.hpp"
#include "../colors.h"


PickUpItemAction::PickUpItemAction(Entity* actor, Item* item) : Action(actor, 100), item(item) {}

void PickUpItemAction::execute() {
    bool pickedUp = actor->inventory->putIn(item);
    if (pickedUp) {
        engine->gui->message(Color::lightestBlue, tcod::stringf("%s picked up %s", actor->name, item->owner->name));
        engine->map->entities.remove(item->owner);
    }
    actor->being->restoreStats(this->time);
}
