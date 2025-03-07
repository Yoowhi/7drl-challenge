#include "PlayerController.hpp"
#include "Engine.hpp"
#include "actions/AttackAction.hpp"
#include "actions/MoveAction.hpp"
#include "Entity.hpp"
#include "ActionQueue.hpp"

PlayerController::PlayerController(Entity* owner) : Controller(owner) {}

PlayerController::~PlayerController() {}

void PlayerController::update() {
    if (!owner->isAlive()) {
        return;
    }
    int dx = 0, dy = 0;
    switch (engine.lastKey.vk) {
        case TCODK_UP : dy=-1; break;
        case TCODK_DOWN : dy=1; break;
        case TCODK_LEFT : dx=-1; break;
        case TCODK_RIGHT : dx=1; break;
        default:
            break;
    }
    if (dx != 0 || dy != 0) {
        Entity* entity = engine.getAliveEntityByCoord(owner->x + dx, owner->y + dy);
        if (entity) {
            Action* attack = new AttackAction(owner, owner->x + dx, owner->y + dy);
            engine.actions->add(attack);
        } else {
            Action* move = new MoveAction(owner, owner->x + dx, owner->y + dy);
            engine.actions->add(move);
        }
        engine.state = Engine::TURN;
    }
}
