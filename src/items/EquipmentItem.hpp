#pragma once
#include "../Item.hpp"
#include <string>
class Entity;
class Action;
class Being;

class EquipmentItem : public Item {
    public:
        enum Type {
            WEAPON,
            HELMET,
            CHEST,
            GLOVES,
            BOOTS
        } type;
        enum Rarity {
            COMMON,
            UNCOMMON,
            RARE,
            EPIC,
            LEGENDARY
        } rarity;

        EquipmentItem(Entity* owner, Type type, int weight);

        Action* use(Entity* user);
};
