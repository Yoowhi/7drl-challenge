#include "PlayerController.hpp"
#include "Engine.hpp"
#include "actions/AttackAction.hpp"
#include "actions/IdleAction.hpp"
#include "actions/MoveAction.hpp"
#include "actions/PickUpItemAction.hpp"
#include "actions/StairsAction.hpp"
#include "actions/DropItemAction.hpp"
#include "Entity.hpp"
#include "ActionQueue.hpp"
#include "Ctrl.hpp"
#include "Container.hpp"
#include "Item.hpp"

PlayerController::PlayerController(Entity* owner) : Controller(owner) {}

PlayerController::~PlayerController() {}

void PlayerController::update() {
    if (!owner->isAlive()) {
        return;
    }
    Action* action = nullptr;
    if (!engine->input.anyKeyPressed) {
        return;
    }
    switch (engine->input.lastKey) {
        case SDL_SCANCODE_UP : action = moveOrAttack(0, -1); break;
        case SDL_SCANCODE_DOWN : action = moveOrAttack(0, 1); break;
        case SDL_SCANCODE_LEFT : action = moveOrAttack(-1, 0); break;
        case SDL_SCANCODE_RIGHT : action = moveOrAttack(1, 0); break;
        default:
            action = handleScancode(engine->input.lastKey);
            break;
    }
    if (action) {
        engine->actions->add(action);
        engine->state = Engine::TURN;
    }
}

Action* PlayerController::handleScancode(SDL_Scancode keycode) {
    bool shift = engine->input.shift;
    switch (keycode) {
        case Ctrl::UP : return moveOrAttack(0, -1);
        case Ctrl::UPRIGHT : return moveOrAttack(1, -1);
        case Ctrl::RIGHT : return moveOrAttack(1, 0);
        case Ctrl::DOWNRIGHT : return moveOrAttack(1, 1);
        case Ctrl::DOWN : return moveOrAttack(0, 1);
        case Ctrl::DOWNLEFT : return moveOrAttack(-1, 1);
        case Ctrl::LEFT : return moveOrAttack(-1, 0);
        case Ctrl::UPLEFT : return moveOrAttack(-1, -1);
        case Ctrl::IDLE : return new IdleAction(owner);
        case Ctrl::ACTIVATE: return handleActivate();
        case Ctrl::USE0: return shift ? dropFromInventory(0) : useFromInventory(0);
        case Ctrl::USE1: return shift ? dropFromInventory(1) : useFromInventory(1);
        case Ctrl::USE2: return shift ? dropFromInventory(2) : useFromInventory(2);
        case Ctrl::USE3: return shift ? dropFromInventory(3) : useFromInventory(3);
        case Ctrl::USE4: return shift ? dropFromInventory(4) : useFromInventory(4);
        default:
            break;
    }
    return nullptr;
}

Action* PlayerController::handleActivate() {
    Entity* entity = nullptr;
    entity = engine->getItemEntityByCoord(owner->x, owner->y);
    if (entity) {
        return new PickUpItemAction(owner, entity->item);
    }
    entity = engine->getStairsEntityByCoord(owner->x, owner->y);
    if (entity) {
        return new StairsAction(owner, entity->stairs);
    }
    return nullptr;
}

Action* PlayerController::useFromInventory(int id) {
    Item* item = owner->inventory->getItem(id);
    if (!item) {
        return nullptr;
    }
    return item->use(owner);
}

Action* PlayerController::dropFromInventory(int id) {
    Item* item = owner->inventory->getItem(id);
    if (!item) {
        return nullptr;
    }
    return new DropItemAction(owner, item);
}

Action* PlayerController::moveOrAttack(int dx, int dy) {
    Entity* entity = engine->getAliveEntityByCoord(owner->x + dx, owner->y + dy);
    if (entity) {
        Action* attack = new AttackAction(owner, owner->x + dx, owner->y + dy);
        return attack;
    } else {
        Action* move = new MoveAction(owner, owner->x + dx, owner->y + dy);
        return move;
    }
}
