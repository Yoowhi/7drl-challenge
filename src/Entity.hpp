#pragma once
#include "libtcod.hpp"
class Controller;
class Being;
class Container;
class Item;

class Entity {
    public:
        int x, y;
        int symbol;
        TCODColor color;
        char* name;
        bool blocks;

        // components
        Controller* controller;
        Being* being;
        Container* inventory;
        Item* item;

        Entity(int x, int y, int symbol, TCODColor color, char* name, bool blocks);
        ~Entity();
        void update();
        bool isAlive();
};
