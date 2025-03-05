#include "libtcod.hpp"
#include "Controller.hpp"
#include "Being.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "Action.hpp"
#include "ActionQueue.hpp"
#include "GUI.hpp"
#include "Engine.hpp"

Being::Being(Entity* owner, int maxHp, int defence) : owner(owner), maxHp(maxHp), hp(maxHp), defence(defence) {}

Being::~Being() {}

void Being::die() {
    owner->blocks = false;
    owner->color = TCODColor::darkestGrey;
    Tile* tile = engine.map->getTile(owner->x, owner->y);
    tile->backColor = TCODColor::darkerRed;
    tile->backColorFaded = TCODColor::darkestRed;
    engine.gui->message(TCODColor::white, "%s died", owner->name);

    const char* prefix = "dead ";
    size_t newLength = strlen(prefix) + strlen(owner->name) + 1; // +1 for null terminator
    char* newName = new char[newLength];
    strcpy(newName, prefix);
    strcat(newName, owner->name);
    delete[] owner->name;
    owner->name = newName;

    engine.actions->clearFromActor(owner);
}
