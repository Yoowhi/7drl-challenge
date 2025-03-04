#include "libtcod.hpp"
#include "../Controller.hpp"
#include "../Action.hpp"
#include "../Entity.hpp"
#include "../Map.hpp"
#include "../ActionQueue.hpp"
#include "../Engine.hpp"
#include "IdleAction.hpp"

IdleAction::IdleAction(Entity* actor) : Action() {
    this->actor = actor;
    this->priority = 50;
    this->priorityLeft = 50;
}

void IdleAction::execute() {}
