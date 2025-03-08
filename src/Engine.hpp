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
            UPSTAIRS,
            DOWNSTAIRS,
            GAME_OVER,
        } state;
        int screenWidth, screenHeight;
        int fovRadius;
        Map* map = nullptr;
        Entity* player = nullptr;
        TCOD_key_t lastKey;
        TCOD_mouse_t mouse;
        int mouseCellX, mouseCellY;
        ActionQueue* actions = nullptr;
        GUI* gui;
        int currentMapId;
        TCODList<Map*> maps;

        Engine(int screenWidth, int screenHeight);
        ~Engine();

        void start();
        bool isExplored(int x, int y) const;
        bool isInFOV(int x, int y);
        void computeFOV();
        Entity* getAliveEntityByCoord(int x, int y);
        Entity* getItemEntityByCoord(int x, int y);
        Entity* getStairsEntityByCoord(int x, int y);

    protected:
        void update();
        void render();
        void renderMap();
        void clearScreen();
        void renderEntities();
        void toNextMap();
        void toPreviousMap();
        void initMap(Map* map);
        Map* newMap(int lvl);
};

extern Engine engine;
