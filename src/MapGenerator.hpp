#pragma once
class Map;
class Tile;

class MapGenerator {
    public:
        static Map* generate(int lvl, int width, int height);

    private:
        friend class BspListener;

        MapGenerator(int lvl, int width, int height);

        Map* map;
        int lvl;

        void createArea(int x1, int y1, int x2, int y2);
        void createCreatures(int x1, int y1, int x2, int y2);
        void createLoot(int x1, int y1, int x2, int y2);
        Tile* getTile(int x, int y);
};
