#pragma once
#include "../Action.hpp"
class Entity;
class Item;

class PickUpItemAction : public Action {
    public:
        Item* item = nullptr;

        PickUpItemAction(Entity* actor, Item* item);
        void execute();
};
