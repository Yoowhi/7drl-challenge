#include "PickUpItemAction.hpp"
#include "../Engine.hpp"
#include "../Entity.hpp"
#include "../Container.hpp"
#include "../Map.hpp"
#include "../Being.hpp"
#include "../GUI.hpp"

PickUpItemAction::PickUpItemAction(Entity* actor, Item* item) : Action(actor, 100), item(item) {}

void PickUpItemAction::execute() {
    bool pickedUp = actor->inventory->putIn(item);
    if (pickedUp) {
        engine.gui->message(TCODColor::azure, "%s picked up %s", actor->name, item->owner->name);
        engine.map->entities.remove(item->owner);
    }
    actor->being->restoreStamina(this->time);
}
