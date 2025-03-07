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
    Action* action;
    switch (engine.lastKey.vk) {
        case TCODK_UP : action = moveOrAttack(0, -1); break;
        case TCODK_DOWN : action = moveOrAttack(0, 1); break;
        case TCODK_LEFT : action = moveOrAttack(-1, 0); break;
        case TCODK_RIGHT : action = moveOrAttack(1, 0); break;
        case TCODK_CHAR : action = handleChar(engine.lastKey.c);
        default:
            break;
    }
    if (action) {
        engine.actions->add(action);
        engine.state = Engine::TURN;
    }
}

Action* PlayerController::handleChar(int ascii) {
    switch (ascii) {
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
        case Ctrl::USE0: return useFromInventory(0);
        case Ctrl::USE1: return useFromInventory(1);
        case Ctrl::USE2: return useFromInventory(2);
        case Ctrl::USE3: return useFromInventory(3);
        case Ctrl::USE4: return useFromInventory(4);
        case Ctrl::USE5: return useFromInventory(5);
        case Ctrl::DROP0: return dropFromInventory(0);
        case Ctrl::DROP1: return dropFromInventory(1);
        case Ctrl::DROP2: return dropFromInventory(2);
        case Ctrl::DROP3: return dropFromInventory(3);
        case Ctrl::DROP4: return dropFromInventory(4);
        case Ctrl::DROP5: return dropFromInventory(5);
            /* code */
            break;

        default:
            break;
    }
}

Action* PlayerController::handleActivate() {
    Entity* entity;
    entity = engine.getItemEntityByCoord(owner->x, owner->y);
    if (entity) {
        return new PickUpItemAction(owner, entity->item);
    }
    entity = engine.getStairsEntityByCoord(owner->x, owner->y);
    if (entity) {
        return new StairsAction(owner, entity->stairs);
    }
    return NULL;
}

Action* PlayerController::useFromInventory(int id) {

    Item* item = owner->inventory->getItem(id);
    if (!item) {
        return NULL;
    }
    return item->use(owner);
}

Action* PlayerController::dropFromInventory(int id) {
    Item* item = owner->inventory->getItem(id);
    if (!item) {
        return NULL;
    }
    return new DropItemAction(owner, item);
}

Action* PlayerController::moveOrAttack(int dx, int dy) {
    Entity* entity = engine.getAliveEntityByCoord(owner->x + dx, owner->y + dy);
    if (entity) {
        Action* attack = new AttackAction(owner, owner->x + dx, owner->y + dy);
        return attack;
    } else {
        Action* move = new MoveAction(owner, owner->x + dx, owner->y + dy);
        return move;
    }
}
