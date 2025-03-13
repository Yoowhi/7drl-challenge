#include "libtcod.hpp"
#include "utility.hpp"
#include "MapGenerator.hpp"
#include "CreatureFactory.hpp"
#include "ItemFactory.hpp"
#include "Map.hpp"
#include "Entity.hpp"
#include "colors.h"

static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 4;

class BspListener : public ITCODBspCallback {
    public:
        int lastRoomX, lastRoomY, lastRoomW, lastRoomH;


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
                    gen.map->upX = x + w / 2;
                    gen.map->upY = y + h / 2;
                    Entity* stairsUp = gen.createStairs(Stairs::UP, gen.map->upX, gen.map->upY);
                    gen.map->entities.push(stairsUp);
                    Tile* tileUp = gen.map->getTile(stairsUp->x, stairsUp->y);
                    tileUp->backColor = multiplyColor(tileUp->backColor, 0.7f);
                    tileUp->backColorFaded = multiplyColor(tileUp->backColorFaded, 0.7f);
                }
                lastX = x + w / 2;
                lastY = y + h / 2;
                roomNum++;
                lastRoomX = x;
                lastRoomY = y;
                lastRoomW = w;
                lastRoomH = h;
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
    bsp.splitRecursive(nullptr, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
    BspListener listener(gen);
    bsp.traverseInvertedLevelOrder(&listener, nullptr);
    int downX = listener.lastRoomX + listener.lastRoomW / 2;
    int downY = listener.lastRoomY + listener.lastRoomH / 2;
    gen.map->downX = downX;
    gen.map->downY = downY;
    Entity* stairsDown = gen.createStairs(Stairs::DOWN, downX, downY);
    gen.map->entities.push(stairsDown);
    Tile* tileDown = gen.map->getTile(stairsDown->x, stairsDown->y);
    tileDown->backColor = multiplyColor(tileDown->backColor, 0.7f);
    tileDown->backColorFaded = multiplyColor(tileDown->backColorFaded, 0.7f);
    return gen.map;
}

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
    static const tcod::ColorRGB floor = tcod::ColorRGB{100, 100, 100};
    static const char* symbols = "'`.,";
    for (int tileX = x1; tileX <= x2; tileX++) {
        for (int tileY = y1; tileY <= y2; tileY++) {
            Tile* tile = map->getTile(tileX, tileY);
            TCODRandom* rng = TCODRandom::getInstance();
            float mult = rng->getFloat(0.9f, 1.0f);
            tile->backColor = multiplyColor(floor, mult);
            tile->backColorFaded = multiplyColor(tile->backColor, 0.5f);
            int symbolId = rng->getInt(0, 40);
            if (symbolId < 4) {
                tile->frontColor = multiplyColor(tile->backColor, 0.9f);
                tile->frontColorFaded = multiplyColor(tile->frontColor, 0.5f);
                tile->ch = symbols[symbolId];
            }
            map->walkMap->setProperties(tileX, tileY, true, true);
        }
    }
}

void MapGenerator::createCreatures(int x1, int y1, int x2, int y2) {
    int monsters = rnd(0, 4);
    for (int i = 0; i < monsters; i++) {
        int randX = rnd(x1, x2);
        int randY = rnd(y1, y2);
        if (map->canWalk(randX, randY)) {
            Entity* creature = CreatureFactory::randomCreature(lvl, randX, randY);
            map->entities.push(creature);
        }
    }

}

void MapGenerator::createLoot(int x1, int y1, int x2, int y2) {
    int loot = rnd(0, 1);
    for (int i = 0; i < loot; i++) {
        int randX = rnd(x1, x2);
        int randY = rnd(y1, y2);
        if (map->canWalk(randX, randY)) {
            Entity* item = ItemFactory::createItem(lvl, randX, randY);
            map->entities.push(item);
        }
    }
}

Entity* MapGenerator::createStairs(Stairs::Direction direction, int x, int y) {
    Entity* entity;
    switch (direction) {
        case Stairs::UP:
            entity = new Entity(x, y, '<', Color::lightAmber, "Stairs Up", false); break;
        case Stairs::DOWN:
            entity = new Entity(x, y, '>', Color::darkAmber, "Stairs Down", false); break;
        default:
            throw "Invalid choise in equipment ItemFactory";
    }
    entity->stairs = new Stairs(direction);
    return entity;
}
