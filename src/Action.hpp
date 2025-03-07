#pragma once
#include "Entity.hpp"
class Entity;

class Action {
    public:
        Entity* actor;
        int time;
        int timeLeft;

        Action(Entity* actor, int time);
        virtual void execute() = 0;
};
