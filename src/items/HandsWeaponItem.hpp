#pragma once
#include "WeaponItem.hpp"
class Entity;
class Action;
class Being;

class HandsWeaponItem : public WeaponItem {
    public:
        HandsWeaponItem(Entity* owner, Being* being);

        std::string getPrintStats(Being* being);
        float getMinDamage() override;
        float getMaxDamage() override;
        int getAttackSpeed() override;

    private:
        Being* being;

};
