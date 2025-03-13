#pragma once
#include <string>
class Entity;
class Action;
class Being;

class Item {
    public:
        Entity* owner = nullptr;
        int weight;

        Item(Entity* owner, int weight);

        virtual ~Item() = default;
        virtual Action* use(Entity* user) = 0;
        virtual std::string getPrintStats(Being* being) = 0;
};
