#include "libtcod.hpp"
#include "Controller.hpp"
#include "Entity.hpp"
#include "Creatures.hpp"
#include "Map.hpp"
#include "MapGenerator.hpp"

static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 4;

class BspListener : public ITCODBspCallback {
    public:
        BspListener(MapGenerator& gen) : gen(gen), roomNum(0) {}

        bool visitNode(TCODBsp* node, void* userData) {
            if (node->isLeaf()) {
            int x, y, w, h;
            TCODRandom* rng = TCODRandom::getInstance();
            w = rng->getInt(ROOM_MIN_SIZE, node->w - 2);
            h = rng->getInt(ROOM_MIN_SIZE, node->h - 2);
            x = rng->getInt(node->x + 1, node->x + node->w - w - 1);
            y = rng->getInt(node->y + 1, node->y + node->h - h - 1);
            gen.createArea(x, y, x + w - 1, y + h - 1);
            gen.createLoot(x, y, x + w - 1, y + h - 1);
            if (roomNum != 0) {
                gen.createCreatures(x, y, x + w - 1, y + h - 1);
                gen.createArea(lastX, lastY, x + w / 2, lastY);
                gen.createArea(x + w / 2, lastY, x + w / 2, y + h / 2);
            } else {
                gen.map->enterX = x + w / 2;
                gen.map->enterY = y + h / 2;
            }
            lastX = x + w / 2;
            lastY = y + h / 2;
            roomNum++;
            }
            return true;
        }

    private:
        MapGenerator& gen;
        int roomNum;
        int lastX, lastY;
};

MapGenerator::MapGenerator(int lvl, int width, int height) : lvl(lvl) {
    map = new Map();
    map->lvl = lvl;
    map->width = width;
    map->height = height;
    map->tiles = new Tile[width * height];
    map->walkMap = new TCODMap(width, height);
}

Map* MapGenerator::generate(int lvl, int width, int height) {
    MapGenerator gen(lvl, width, height);
    TCODBsp bsp(0, 0, width, height);
    bsp.splitRecursive(NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
    BspListener listener(gen);
    bsp.traverseInvertedLevelOrder(&listener, NULL);
    return gen.map;
}

Tile* MapGenerator::getTile(int x, int y) { return &map->tiles[x + y * map->width]; }

void MapGenerator::createArea(int x1, int y1, int x2, int y2) {
    if (x2 < x1) {
        int tmp = x2;
        x2 = x1;
        x1 = tmp;
    }
    if (y2 < y1) {
        int tmp = y2;
        y2 = y1;
        y1 = tmp;
    }
    static const TCODColor floor(100, 100, 100);
    static const TCODColor wall(128, 128, 128);
    static const char* symbols = "'`.,";
    for (int tileX = x1; tileX <= x2; tileX++) {
        for (int tileY = y1; tileY <= y2; tileY++) {
            Tile* tile = getTile(tileX, tileY);
            TCODRandom* rng = TCODRandom::getInstance();
            float mult = rng->getFloat(0.9f, 1.0f);
            tile->backColor = floor * mult;
            tile->backColorFaded = tile->backColor * 0.5f;
            int symbolId = rng->getInt(0, 40);
            if (symbolId < 4) {
                tile->frontColor = tile->backColor * 0.9f;
                tile->frontColorFaded = tile->frontColor * 0.5f;
                tile->ch = symbols[symbolId];
            }
            map->walkMap->setProperties(tileX, tileY, true, true);
        }
    }
}

void MapGenerator::createCreatures(int x1, int y1, int x2, int y2) {
    TCODRandom* rng = TCODRandom::getInstance();
    int monsters = rng->getInt(0, 4);
    for (int i = 0; i < monsters; i++) {
        int randX = rng->getInt(x1, x2);
        int randY = rng->getInt(y1, y2);
        if (map->canWalk(randX, randY)) {
            Entity* creature = Creatures::randomCreature(lvl, randX, randY);
            map->entities.push(creature);
        }
    }

}

void MapGenerator::createLoot(int x1, int y1, int x2, int y2) {}
