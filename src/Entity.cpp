#include "Entity.hpp"
#include "Controller.hpp"
#include "Being.hpp"
#include "Stairs.hpp"
#include "Container.hpp"
#include "Item.hpp"

Entity::Entity(int x, int y, int symbol, tcod::ColorRGB color, char* name, bool blocks)
    : x(x), y(y), symbol(symbol), color(color), blocks(blocks) {
        this->name = new char[strlen(name)];
        strcpy(this->name, name);
    }

Entity::~Entity() {
    delete[] name;
    if (controller) delete controller;
    if (being) delete being;
    if (inventory) delete inventory;
    if (item) delete item;
    if (stairs) delete stairs;
}

void Entity::update() {
    if (controller) {
        controller->update();
    }
}

bool Entity::isAlive() {
    return being != nullptr && being->hp > 0;
}
