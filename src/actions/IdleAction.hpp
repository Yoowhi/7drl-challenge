#pragma once
#include "../Action.hpp"
class Entity;

class IdleAction : public Action {
    public:
        int x, y;

        IdleAction(Entity* actor);
        void execute();
};
