#pragma once
#include "items/EquipmentItem.hpp"
class Entity;

class Equipment {
    public:
        Entity* owner;
        std::unordered_map<EquipmentItem::Type, EquipmentItem*> items;

        Equipment(Entity* owner);
        EquipmentItem* swapItem(EquipmentItem* item);
        EquipmentItem* getItem(EquipmentItem::Type type);

};
