#pragma once
#include "../Item.hpp"
class Entity;
class Action;

class PotionItem : public Item {
    public:
        float hp;
        float stamina;

        PotionItem(Entity* owner);

        Action* use(Entity* user);
};
