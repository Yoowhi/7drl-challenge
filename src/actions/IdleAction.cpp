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
    this->time = 50;
    this->timeLeft = 50;
}

void IdleAction::execute() {}
