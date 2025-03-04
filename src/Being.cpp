#include "libtcod.hpp"
#include "Being.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "Engine.hpp"

Being::Being(Entity* owner, int maxHp, int defence) : owner(owner), maxHp(maxHp), hp(maxHp) {}

Being::~Being() {}

void Being::die() {
    owner->blocks = false;
    owner->color = TCODColor::lightestGrey;
    Tile* tile = engine.map->getTile(owner->x, owner->y);
    // TODO: avoid uint8_t overflow
    tile->backColor.r *= 1.5f;
    tile->backColorFaded.r *= 1.5f;

    char* newName = new char[strlen(owner->name) + 5 + 1]; // "dead " = 5
    strcpy(newName, owner->name);
    strcat(newName, "dead ");
    delete[] owner->name;
    owner->name = newName;
}
