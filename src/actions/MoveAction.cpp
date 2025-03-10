#include "MoveAction.hpp"
#include "../Engine.hpp"
#include "../Map.hpp"
#include "../Entity.hpp"
#include "../Being.hpp"

MoveAction::MoveAction(Entity* actor, int x, int y) : Action(actor, 100), x(x), y(y) {}

void MoveAction::execute() {
    if (engine->map->canWalk(x, y)) {
        actor->x = x;
        actor->y = y;
    } else if (engine->map->canWalk(actor->x, y)) {
        actor->y = y;
    } else if (engine->map->canWalk(x, actor->y)) {
        actor->x = x;
    }
    actor->being->restoreStamina(this->time);
}
