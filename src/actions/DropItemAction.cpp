#include "DropItemAction.hpp"
#include "../Engine.hpp"
#include "../Entity.hpp"
#include "../Container.hpp"
#include "../Map.hpp"
#include "../Item.hpp"
#include "../Being.hpp"

DropItemAction::DropItemAction(Entity* actor, Item* item) : Action(actor, 100), item(item) {}

void DropItemAction::execute() {
    actor->inventory->remove(item);
    item->owner->x = actor->x;
    item->owner->y = actor->y;
    engine.map->entities.push(item->owner);
    actor->being->restoreStamina(this->time);
}
