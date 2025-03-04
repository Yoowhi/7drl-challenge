#include "libtcod.hpp"
#include "Controller.hpp"
#include "CreatureController.hpp"
#include "Entity.hpp"
#include "Action.hpp"
#include "actions/MoveAction.hpp"
#include "actions/IdleAction.hpp"
#include "actions/AttackAction.hpp"
#include "ActionQueue.hpp"
#include "Engine.hpp"

CreatureController::CreatureController(Entity* owner) : Controller(owner) {}

CreatureController::~CreatureController() {}

void CreatureController::update() {
    if (!owner->isAlive()) {
        return;
    }
    if (engine.isInFOV(owner->x, owner->y)) {
        int dX = owner->x - engine.player->x;
        int dY = owner->y - engine.player->y;
        int stepDx = (dX < 0 ? 1 : -1);
        int stepDy = (dY < 0 ? 1 : -1);
        if (owner->x == engine.player->x) stepDx = 0;
        if (owner->y == engine.player->y) stepDy = 0;
        float distance = sqrtf(dX * dX + dY * dY);
        if (distance > 1) {
            Action* move = new MoveAction(owner, owner->x + stepDx, owner->y + stepDy);
            engine.actions->add(move);
        } else {
            Action* attack = new AttackAction(owner, owner->x + stepDx, owner->y + stepDy);
            engine.actions->add(attack);
        }
    } else {
        Action* idle = new IdleAction(owner);
        engine.actions->add(idle);
    }
}
