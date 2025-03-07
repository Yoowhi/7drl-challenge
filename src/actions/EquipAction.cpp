#include "libtcod.hpp"
#include "../Controller.hpp"
#include "../Action.hpp"
#include "../Entity.hpp"
#include "../Equipment.hpp"
#include "../Being.hpp"
#include "../Map.hpp"
#include "../ActionQueue.hpp"
#include "../Engine.hpp"
#include "../items/EquipmentItem.hpp"
#include "../Container.hpp"
#include "EquipAction.hpp"

EquipAction::EquipAction(Entity* actor, EquipmentItem* item) : Action(actor, 100), item(item) {}

void EquipAction::execute() {
    actor->inventory->remove(item);
    if (item) {
        EquipmentItem* extractedItem = actor->being->equipment.swapItem(item);
        actor->inventory->putIn(extractedItem);
    }
    actor->being->restoreStamina(this->time);
}
