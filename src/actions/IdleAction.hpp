#pragma once
#include "../Action.hpp"
class Entity;

class IdleAction : public Action {
    public:

        IdleAction(Entity* actor);
        void execute();
};
