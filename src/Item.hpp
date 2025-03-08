#pragma once
class Entity;
class Action;

class Item {
    public:
        Entity* owner = nullptr;

        Item(Entity* owner);

        virtual Action* use(Entity* user) = 0;
};
