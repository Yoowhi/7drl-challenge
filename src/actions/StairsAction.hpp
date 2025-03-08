#pragma once
#include "../Action.hpp"
class Entity;
class Stairs;

class StairsAction : public Action {
    public:
        Stairs* stairs = nullptr;

        StairsAction(Entity* actor, Stairs* stairs);
        void execute();
};
