#pragma once
#include "../Action.hpp"
class Entity;
class Stairs;

class StairsAction : public Action {
    public:
        Stairs* stairs;

        StairsAction(Entity* actor, Stairs* stairs);
        void execute();
};
