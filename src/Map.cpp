#include "libtcod.hpp"
#include "Controller.hpp"
#include "Entity.hpp"
#include "Map.hpp"

Map::Map() {}

Map::~Map() {
    delete[] tiles;
    delete walkMap;
    entities.clearAndDelete();
}

void Map::enter(Entity* entity) {
    entities.push(entity);
    entity->x = enterX;
    entity->y = enterY;
}

void Map::exit(Entity* entity) {
    entities.remove(entity);
}

bool Map::canWalk(int x, int y) {
    if (!walkMap->isWalkable(x, y)) {
        return false;
    }
    for (Entity** iter = entities.begin(); iter != entities.end(); iter++) {
        Entity* entity = *iter;
        if (entity->blocks && entity->x == x && entity->y == y) {
            return false;
        }
    }
    return true;
}
