#include "libtcod.hpp"
#include "Controller.hpp"
#include "Entity.hpp"
#include "PlayerController.hpp"
#include "Map.hpp"
#include "MapGenerator.hpp"
#include "Action.hpp"
#include "ActionQueue.hpp"
#include "Engine.hpp"

static const int FOV_RADIUS = 10;

Engine::Engine(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight), state(INPUT), fovRadius(FOV_RADIUS) {
    TCODConsole::initRoot(80, 50, "kek", false);
    player = new Entity(0, 0, '@', TCODColor::white, "Hero", true);
    player->controller = new PlayerController(player);
    map = MapGenerator::generate(1, 80, 50);
    map->enter(player);
    computeFOV();
    actions = new ActionQueue();
}

Engine::~Engine() {
    delete map;
    delete actions;
}

void Engine::start() {
    while (!TCODConsole::isWindowClosed()) {
        update();
        render();
    }
}

void Engine::update() {
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, &mouse);
    if (state == INPUT) {
        player->update();
        return;
    }
    Action* action = actions->next();
    if (!action) {
        return;
    }
    action->execute();
    if (action->actor == player) {
        computeFOV();
        state = INPUT;
    } else {
        action->actor->update();
    }
}

void Engine::render() {
    renderMap();
    renderEntities();
    TCODConsole::flush();
}

void Engine::renderMap() {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            Tile* tile = &map->tiles[x + y * map->width];
            if (isInFOV(x, y)) {
                TCODConsole::root->putCharEx(x, y, tile->ch, tile->frontColor, tile->backColor);
            } else if (isExplored(x, y)) {
                TCODConsole::root->putCharEx(x, y, tile->ch, tile->frontColorFaded, tile->backColorFaded);
            }
        }
    }
}

void Engine::renderEntities() {
    for(Entity** iter = map->entities.begin(); iter != map->entities.end(); iter++) {
        Entity* entity = *iter;
        if (isInFOV(entity->x, entity->y)) {
            TCODConsole::root->setChar(entity->x, entity->y, entity->symbol);
            TCODConsole::root->setCharForeground(entity->x, entity->y, entity->color);
        }
    }
}

void Engine::computeFOV() {
    map->walkMap->computeFov(player->x, player->y, fovRadius);
}

bool Engine::isExplored(int x, int y) const {
    return map->tiles[x + y * map->width].explored;
}

bool Engine::isInFOV(int x, int y) {
    if ( x < 0 || x >= map->width || y < 0 || y >= map->height ) {
        return false;
    }
    if (map->walkMap->isInFov(x, y)) {
        map->tiles[x + y * map->width].explored = true;
        return true;
    }
    return false;
}
