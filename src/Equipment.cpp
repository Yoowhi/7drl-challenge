#include "Equipment.hpp"
#include "Entity.hpp"
#include "Being.hpp"

Equipment::Equipment(Entity* owner) : owner(owner) {}

EquipmentItem* Equipment::swapItem(EquipmentItem* item) {
    EquipmentItem* equipedItem = items[item->type];
    if (equipedItem == owner->being->handsWeapon) {
        equipedItem = nullptr;
    }
    items[item->type] = item;
    return equipedItem;
}

EquipmentItem* Equipment::getItem(EquipmentItem::Type type) {
    EquipmentItem* equipedItem = items[type];
    // if (type == EquipmentItem::WEAPON && equipedItem == nullptr) {
    //     return (EquipmentItem*)owner->being->handsWeapon;
    // }
    return equipedItem;
}
