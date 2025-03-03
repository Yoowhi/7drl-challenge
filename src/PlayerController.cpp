#include "libtcod.hpp"
#include "Controller.hpp"
#include "PlayerController.hpp"
#include "Entity.hpp"
#include "Action.hpp"
#include "actions/MoveAction.hpp"
#include "ActionQueue.hpp"
#include "Engine.hpp"

PlayerController::PlayerController(Entity* owner) : Controller(owner) {}

PlayerController::~PlayerController() {}

void PlayerController::update() {
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
        engine.state = Engine::TURN;
        Action* move = new MoveAction(owner, owner->x + dx, owner->y + dy);
        engine.actions->add(move);
    }
}
