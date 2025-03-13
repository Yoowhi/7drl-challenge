#pragma once
#include "Equipment.hpp"
class Entity;
class EquipmentItem;

class Being {
    public:
        float hp;
        float stamina;
        float defense;
        int lvl;
        int xp;
        int attributePoints;


        int strength; // attack damage
        int health; // amount of health points
        int agility; // speed of actions
        int endurance; // stamina
        Equipment equipment;

        EquipmentItem* handsWeapon = nullptr;
        Entity* owner = nullptr;

        Being(
            Entity* owner,
            int lvl,
            float baseHp,
            float baseStamina,
            int strength,
            int health,
            int agility,
            int endurance,
            int xpForKill
        );
        ~Being();

        float getTimeMultiplier();
        float getDamageMultiplier();
        float getMaxDefense();
        int getSumWeight();
        float getMaxHp();
        float getMaxStamina();
        void updateHp(float hp);
        void updateStamina(float stamina);
        void updateDefense(float defense);
        void restoreStats(int time);
        void addXp(int amount);
        int getMaxXp();
        void autoIncreaseAttributes(int lvlUps, int priorityStrength, int priorityHealth, int priorityAgility, int priorityEndurance);
        void die();
        int getXpForKill();
        void incrementStrength();
        void incrementHealth();
        void incrementAgility();
        void incrementEndurance();

    private:
        float baseHp;
        float baseStamina;
        int xpForKill;

};
