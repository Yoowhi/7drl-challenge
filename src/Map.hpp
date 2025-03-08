#pragma once
#include "libtcod.hpp"
#include "MapGenerator.hpp"
class Entity;

struct Tile {
  int ch;
  TCODColor frontColor;
  TCODColor backColor;
  TCODColor frontColorFaded;
  TCODColor backColorFaded;
  bool explored;

  Tile() : explored(false), backColor(TCODColor(128, 128, 128)), frontColor(TCODColor(100, 100, 100)), backColorFaded(TCODColor(64, 64, 64)), frontColorFaded(TCODColor(50, 50, 50)) {};
};

class Map {
    public:
        ~Map();
        int width, height;
        int upX, upY;
        int downX, downY;
        int lvl;
        Tile* tiles = nullptr;
        TCODList<Entity*> entities;
        TCODMap* walkMap = nullptr;

        void enterFromUp(Entity* entity);
        void enterFromDown(Entity* entity);
        void exit(Entity* entity);
        bool canWalk(int x, int y);
        Tile* getTile(int x, int y);

    private:
        friend class MapGenerator;

        Map();

};
