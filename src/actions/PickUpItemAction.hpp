#pragma once
#include "../Action.hpp"
#include "../Entity.hpp"
#include "../Item.hpp"
class Entity;
class Item;

class PickUpItemAction : public Action {
    public:
        Item* item;

        PickUpItemAction(Entity* actor, Item* item);
        void execute();
};
