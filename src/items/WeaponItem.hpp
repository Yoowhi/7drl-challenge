#pragma once
#include "EquipmentItem.hpp"
class Entity;
class Action;
class Being;

class WeaponItem : public EquipmentItem {
    public:
        WeaponItem(Entity* owner, int weight, float minDamage, float maxDamage, int attackSpeed);

        virtual std::string getPrintStats(Being* being);
        virtual float getMinDamage();
        virtual float getMaxDamage();
        virtual int getAttackSpeed();

    private:
        float minDamage;
        float maxDamage;
        int attackSpeed;

};
