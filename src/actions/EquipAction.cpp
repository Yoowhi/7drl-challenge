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
