#pragma once
#include "libtcod.hpp"
#include "SDL.h"
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
        int screenWidthCells, screenHeightCells;
        int fovRadius;

        struct Input {
            bool keysPressed[SDL_NUM_SCANCODES] = { false };
            bool anyKeyPressed = false;
            SDL_Scancode lastKey;
            int mouseCellX = 0;
            int mouseCellY = 0;
            bool shift = false;
        } input;



        int currentMapId;
        SDL_Event event;
        tcod::Console* console = nullptr;
        tcod::Context* context = nullptr;
        Map* map = nullptr;
        Entity* player = nullptr;
        ActionQueue* actions = nullptr;
        GUI* gui;
        TCODList<Map*> maps;

        Engine(int screenWidthCells, int screenHeightCells, tcod::Console* consol, tcod::Context* context);
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
        void renderEntities();
        void toNextMap();
        void toPreviousMap();
        void initMap(Map* map);
        Map* newMap(int lvl);
        bool isCharacterKey(SDL_Keycode keycode);
};

extern Engine* engine;
