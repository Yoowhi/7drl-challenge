#pragma once
#include "../Item.hpp"
class Entity;
class Action;

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
        float minDamage;
        float maxDamage;
        int defence;
        int weight;

        EquipmentItem(Entity* owner, Type type);

        Action* use(Entity* user);
};
