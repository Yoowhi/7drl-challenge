#include "EquipAction.hpp"
#include "../Entity.hpp"
#include "../Container.hpp"
#include "../Being.hpp"
#include "../Engine.hpp"
#include "../GUI.hpp"


EquipAction::EquipAction(Entity* actor, EquipmentItem* item) : Action(actor, 100), item(item) {}

void EquipAction::execute() {
    actor->inventory->remove(item);
    EquipmentItem* extractedItem = actor->being->equipment.swapItem(item);
    if (extractedItem) {
        bool puttedIn = actor->inventory->putIn(extractedItem);
        if (!puttedIn) {
            throw std::runtime_error("No place for extracted equipmend during EquipAction");
        }
        engine.gui->message(TCODColor::azure, "%s equipped %s", actor->name, item->owner->name);
    }

    actor->being->restoreStamina(this->time);
}
