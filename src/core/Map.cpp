#include "libtcod.hpp"
#include "Map.hpp"

Map::Map() {}

Map::~Map() {
    delete[] tiles;
    delete walkMap;
}
