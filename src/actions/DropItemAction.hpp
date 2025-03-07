#pragma once
#include "../Action.hpp"
class Entity;
class Item;

class DropItemAction : public Action {
    public:
        Item* item;

        DropItemAction(Entity* actor, Item* item);
        void execute();
};
