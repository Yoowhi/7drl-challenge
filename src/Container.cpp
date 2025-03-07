#include <unordered_map>
#include "libtcod.hpp"
#include "Controller.hpp"
#include "CreatureController.hpp"
#include "Entity.hpp"
#include "Being.hpp"
#include "Action.hpp"
#include "actions/MoveAction.hpp"
#include "actions/IdleAction.hpp"
#include "actions/AttackAction.hpp"
#include "ActionQueue.hpp"
#include "GUI.hpp"
#include "Engine.hpp"
#include "Item.hpp"
#include "EquipmentItem.hpp"
#include "Container.hpp"
#include <stdexcept>

Container::Container(Entity* owner) : owner(owner) {}


bool Container::putIn(Item* item) {
    for (int i = 0; i < CONTAINER_SIZE; i++) {
        if (!items[i]) {
            items[i] = item;
            return true;
        }
    }
    return false;
}

Item* Container::getOut(int id) {
    if (id >= CONTAINER_SIZE || id < 0) {
        throw std::runtime_error("Requested item ID from Container is larger than CONTAINER_SIZE");
    }
    Item* item = items[id];
    items[id] = NULL;
    return item;
}

void Container::remove(Item* item) {
    for (int i = 0; i < CONTAINER_SIZE; i++) {
        if (item == items[i]) {
            items[i] = NULL;
        }
    }
    throw std::runtime_error("Requested item not found in Container");
}
