#pragma once
#include "libtcod.hpp"
class ActionQueue;
class Entity;
class Map;
class GUI;

class Engine {
    public:
        enum State {
            INPUT,
            TURN,
            GAME_OVER,
        } state;
        int screenWidth, screenHeight;
        int fovRadius;
        Map* map;
        Entity* player;
        TCOD_key_t lastKey;
        TCOD_mouse_t mouse;
        int mouseCellX, mouseCellY;
        ActionQueue* actions;
        GUI* gui;

        Engine(int screenWidth, int screenHeight);
        ~Engine();

        void start();
        bool isExplored(int x, int y) const;
        bool isInFOV(int x, int y);
        void computeFOV();
        Entity* getAliveEntityByCoord(int x, int y);

    protected:
        void update();
        void render();
        void renderMap();
        void renderEntities();
};

extern Engine engine;
