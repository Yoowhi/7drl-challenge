#pragma once
#include "libtcod.hpp"
class Controller;
class Being;
class Container;
class Item;
class Stairs;

class Entity {
    public:
        int x, y;
        int symbol;
        tcod::ColorRGB color;
        char* name = nullptr;
        bool blocks;

        // components
        Controller* controller = nullptr;
        Being* being = nullptr;
        Container* inventory = nullptr;
        Item* item = nullptr;
        Stairs* stairs = nullptr;

        Entity(int x, int y, int symbol, tcod::ColorRGB color, char* name, bool blocks);
        ~Entity();
        void update();
        bool isAlive();
};
