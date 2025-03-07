#include "IdleAction.hpp"

IdleAction::IdleAction(Entity* actor) : Action(actor, 100) {
}

void IdleAction::execute() {
    actor->being->restoreStamina(this->time);
}
