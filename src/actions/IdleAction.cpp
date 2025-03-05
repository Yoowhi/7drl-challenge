#include "libtcod.hpp"
#include "../Controller.hpp"
#include "../Action.hpp"
#include "../Entity.hpp"
#include "../Being.hpp"
#include "../Map.hpp"
#include "../ActionQueue.hpp"
#include "../Engine.hpp"
#include "IdleAction.hpp"

IdleAction::IdleAction(Entity* actor) : Action(actor, 100) {
}

void IdleAction::execute() {
    actor->being->restoreStamina(this->time);
}
