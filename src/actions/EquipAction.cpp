#include "EquipAction.hpp"
#include "../Entity.hpp"
#include "../Container.hpp"
#include "../Being.hpp"


EquipAction::EquipAction(Entity* actor, EquipmentItem* item) : Action(actor, 100), item(item) {}

void EquipAction::execute() {
    actor->inventory->remove(item);
    if (item) {
        EquipmentItem* extractedItem = actor->being->equipment.swapItem(item);
        actor->inventory->putIn(extractedItem);
    }
    actor->being->restoreStamina(this->time);
}
