#include "PickUpItemAction.hpp"
#include "../Engine.hpp"

PickUpItemAction::PickUpItemAction(Entity* actor, Item* item) : Action(actor, 100), item(item) {}

void PickUpItemAction::execute() {
    bool pickedUp = actor->inventory->putIn(item);
    if (pickedUp) {
        engine.map->entities.remove(item->owner);
    }
    actor->being->restoreStamina(this->time);
}
