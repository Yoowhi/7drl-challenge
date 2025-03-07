#include "Equipment.hpp"

Equipment::Equipment(Entity* owner) : owner(owner) {}

EquipmentItem* Equipment::swapItem(EquipmentItem* item) {
    EquipmentItem* equipedItem = items[item->type];
    items[item->type] = item;
    return equipedItem;
}

EquipmentItem* Equipment::getItem(EquipmentItem::Type type) {
    return items[type];
}
