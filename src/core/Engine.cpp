#include "libtcod.hpp"
#include "Map.hpp"
#include "MapGenerator.hpp"
#include "Engine.hpp"

Engine::Engine(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight) {
    TCODConsole::initRoot(80, 50, "kek", false);
    map = MapGenerator::generate(1, 80, 50);
}

Engine::~Engine() { delete map; }

void Engine::start() {
    while (!TCODConsole::isWindowClosed()) {
        update();
        render();
    }
}

void Engine::update() { TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, &mouse); }

void Engine::render() {
    renderMap();
    TCODConsole::flush();
}

void Engine::renderMap() {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            Tile* tile = &map->tiles[x + y * map->width];
            TCODConsole::root->putCharEx(x, y, tile->ch, tile->frontColor, tile->backColor);
        }
    }
}
