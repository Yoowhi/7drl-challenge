#include "libtcod.hpp"
#include "Controller.hpp"
#include "Entity.hpp"

Entity::Entity(int x, int y, int symbol, TCODColor color, const char* nam, bool blocks)
    : x(x), y(y), symbol(symbol), color(color), name(name), blocks(blocks) {}

Entity::~Entity() {
    delete name;
}

void Entity::update() {
    if (controller) {
        controller->update();
    }
}
