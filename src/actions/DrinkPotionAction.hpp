#pragma once
#include "../Action.hpp"
class Entity;
class PotionItem;

class DrinkPotionAction : public Action {
    public:
        PotionItem* item = nullptr;

        DrinkPotionAction(Entity* actor, PotionItem* item);
        void execute();
};
