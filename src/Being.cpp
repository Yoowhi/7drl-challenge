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

    // char* newName = new char[strlen(owner->name) + 5 + 1]; // "dead " = 5
    // strcpy(newName, owner->name);
    // strcat(newName, "dead ");
    // delete[] owner->name;
    // owner->name = newName;
    engine.actions->clearFromActor(owner);
}
