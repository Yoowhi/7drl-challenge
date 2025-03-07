#include "libtcod.hpp"
#include "../Controller.hpp"
#include "../Action.hpp"
#include "../Entity.hpp"
#include "../Equipment.hpp"
#include "../Being.hpp"
#include "../Map.hpp"
#include "../ActionQueue.hpp"
#include "../Engine.hpp"
#include "../Item.hpp"
#include "../items/EquipmentItem.hpp"
#include "../Container.hpp"
#include "PickUpItemAction.hpp"

PickUpItemAction::PickUpItemAction(Entity* actor, Item* item) : Action(actor, 100), item(item) {}

void PickUpItemAction::execute() {
    bool pickedUp = actor->inventory->putIn(item);
    if (pickedUp) {
        engine.map->entities.remove(item->owner);
    }
    actor->being->restoreStamina(this->time);
}
