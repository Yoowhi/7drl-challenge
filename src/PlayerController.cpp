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
    switch (engine.lastKey.vk) {
        case TCODK_UP : action = moveOrAttack(0, -1); break;
        case TCODK_DOWN : action = moveOrAttack(0, 1); break;
        case TCODK_LEFT : action = moveOrAttack(-1, 0); break;
        case TCODK_RIGHT : action = moveOrAttack(1, 0); break;
        case TCODK_CHAR : action = handleChar(engine.lastKey.c); break;
        default:
            break;
    }
    if (action) {
        engine.actions->add(action);
        engine.state = Engine::TURN;
    }
}

// Ctrl intToCtrl(char ch) {
//     switch (ch) {
//         case 'w': return UP;
//         case 'e': return UPRIGHT;
//         case 'd': return RIGHT;
//         case 'c': return DOWNRIGHT;
//         case 'x': return DOWN;
//         case 'z': return DOWNLEFT;
//         case 'a': return LEFT;
//         case 'q': return UPLEFT;
//         case 's': return IDLE;
//         case 'f': return ACTIVATE;
//         case 'p': return USE0;
//         case '2': return USE1;
//         case '3': return USE2;
//         case '4': return USE3;
//         case '5': return USE4;
//         case '6': return USE5;
//         case '!': return DROP0;
//         case '@': return DROP1;
//         case '#': return DROP2;
//         case '$': return DROP3;
//         case '%': return DROP4;
//         case '^': return DROP5;
//         default: return NO_ACTION;
//     }
// }

Action* PlayerController::handleChar(char& ascii) {
    bool shift = engine.lastKey.shift;
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
    entity = engine.getItemEntityByCoord(owner->x, owner->y);
    if (entity) {
        return new PickUpItemAction(owner, entity->item);
    }
    entity = engine.getStairsEntityByCoord(owner->x, owner->y);
    if (entity) {
        return new StairsAction(owner, entity->stairs);
    }
    return nullptr;
}

Action* PlayerController::useFromInventory(int id) {
    if (engine.lastKey.shift) {
        return dropFromInventory(id);
    }
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
    Entity* entity = engine.getAliveEntityByCoord(owner->x + dx, owner->y + dy);
    if (entity) {
        Action* attack = new AttackAction(owner, owner->x + dx, owner->y + dy);
        return attack;
    } else {
        Action* move = new MoveAction(owner, owner->x + dx, owner->y + dy);
        return move;
    }
}
