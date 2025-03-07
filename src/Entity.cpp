#include "libtcod.hpp"
#include "Controller.hpp"
#include "Being.hpp"
#include "Action.hpp"
#include "Item.hpp"
#include "Container.hpp"
#include "Entity.hpp"

Entity::Entity(int x, int y, int symbol, TCODColor color, char* name, bool blocks)
    : x(x), y(y), symbol(symbol), color(color), blocks(blocks) {
        this->name = new char[strlen(name)];
        name = strcpy(this->name, name);
    }

Entity::~Entity() {
    delete[] name;
}

void Entity::update() {
    if (controller) {
        controller->update();
    }
}

bool Entity::isAlive() {
    return being != NULL && being->hp > 0;
}
