#pragma once
#include "EquipmentItem.hpp"
#include <string>
class Entity;
class Action;
class Being;

class ArmorItem : public EquipmentItem {
    public:
        int defence;

        ArmorItem(Entity* owner, EquipmentItem::Type type, int weight, int defense);

        std::string getPrintStats(Being* being);
};
