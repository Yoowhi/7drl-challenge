#pragma once
#include "Stairs.hpp"
class Map;
class Entity;
struct Tile;

class MapGenerator {
    public:
        static Map* generate(int lvl, int width, int height);

    private:
        friend class BspListener;

        MapGenerator(int lvl, int width, int height);

        Map* map = nullptr;
        int lvl;

        void createArea(int x1, int y1, int x2, int y2);
        void createCreatures(int x1, int y1, int x2, int y2);
        void createLoot(int x1, int y1, int x2, int y2);
        Entity* createStairs(Stairs::Direction direction, int x, int y);
};
