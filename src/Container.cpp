#include <unordered_map>
#include "Container.hpp"
#include "Item.hpp"

Container::Container(Entity* owner) : owner(owner) {}

Container::~Container() {
    for(int i = 0; i < CONTAINER_SIZE; i++) {
        delete items[i]->owner;
    }
}


bool Container::putIn(Item* item) {
    for (int i = 0; i < CONTAINER_SIZE; i++) {
        if (!items[i]) {
            items[i] = item;
            return true;
        }
    }
    return false;
}

Item* Container::getItem(int id) {
    if (id >= CONTAINER_SIZE || id < 0) {
        throw std::runtime_error("Requested item ID from Container is larger than CONTAINER_SIZE");
    }
    return items[id];
}

void Container::remove(Item* item) {
    for (int i = 0; i < CONTAINER_SIZE; i++) {
        if (item == items[i]) {
            items[i] = NULL;
            return;

        }
    }
    throw std::runtime_error("Requested item not found in Container");
}

Item* Container::getOut(int id) {
    if (id >= CONTAINER_SIZE || id < 0) {
        throw std::runtime_error("Requested item ID from Container is larger than CONTAINER_SIZE");
    }
    Item* item = items[id];
    items[id] = NULL;
    return item;
}
