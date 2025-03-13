#include "IdleAction.hpp"
#include "../Entity.hpp"
#include "../Being.hpp"

IdleAction::IdleAction(Entity* actor) : Action(actor, 100) {
}

void IdleAction::execute() {
    actor->being->restoreStats(this->time);
}
