#include "libtcod.hpp"
#include "../Controller.hpp"
#include "../Action.hpp"
#include "../Entity.hpp"
#include "../Map.hpp"
#include "../ActionQueue.hpp"
#include "../Engine.hpp"
#include "MoveAction.hpp"

MoveAction::MoveAction(Entity* actor, int x, int y) : Action() {
    this->actor = actor;
    this->priority = 50;
    this->x = x;
    this->y = y;
}

void MoveAction::execute() {
    if (engine.map->canWalk(x, y)) {
        actor->x = x;
        actor->y = y;
    }
}
