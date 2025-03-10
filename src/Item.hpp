#pragma once
#include <string>
class Entity;
class Action;
class Being;

class Item {
    public:
        Entity* owner = nullptr;

        Item(Entity* owner);

        virtual ~Item() = default;
        virtual Action* use(Entity* user) = 0;
        virtual std::string getPrintMainStat(Being* being) = 0;
};
