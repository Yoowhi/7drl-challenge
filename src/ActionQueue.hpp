#pragma once
#include "libtcod.hpp"
#include <vector>
class Entity;
class Action;

class ActionQueue {
    public:
        TCODList<Action*> actions;

        ActionQueue();
        ~ActionQueue();
        void add(Action* action);
        void clearFromActor(Entity* actor);
        Action* next();
};
