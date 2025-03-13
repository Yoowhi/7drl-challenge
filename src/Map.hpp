#pragma once
#include "libtcod.hpp"
#include "MapGenerator.hpp"
#include "colors.h"

class Entity;

struct Tile {
  int ch;
  tcod::ColorRGB frontColor = Color::darkGrey;
  tcod::ColorRGB backColor = Color::grey;
  tcod::ColorRGB frontColorFaded = Color::darkestGrey;
  tcod::ColorRGB backColorFaded = Color::darkerGrey;
  bool explored;

  Tile() : explored(false) {};
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
        void moveEntityToListBegin(Entity* entity);

    private:
        friend class MapGenerator;

        Map();

};
