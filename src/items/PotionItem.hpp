#pragma once
#include "../Item.hpp"
class Entity;
class Action;
class Being;

class PotionItem : public Item {
    public:
        float hp;
        float stamina;

        PotionItem(Entity* owner);

        Action* use(Entity* user);
        std::string getPrintMainStat(Being* being);
};
