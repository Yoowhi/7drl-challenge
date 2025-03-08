#pragma once
#include "items/EquipmentItem.hpp"
#include <unordered_map>
class Entity;

class Equipment {
    public:
        Entity* owner = nullptr;
        std::unordered_map<EquipmentItem::Type, EquipmentItem*> items;

        Equipment(Entity* owner);
        EquipmentItem* swapItem(EquipmentItem* item);
        EquipmentItem* getItem(EquipmentItem::Type type);

};
