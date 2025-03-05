#include "libtcod.hpp"
#include "Controller.hpp"
#include "Being.hpp"
#include "Entity.hpp"
#include "PlayerController.hpp"
#include "Map.hpp"
#include "MapGenerator.hpp"
#include "Action.hpp"
#include "ActionQueue.hpp"
#include "Engine.hpp"
#include "GUI.hpp"

static const int FOV_RADIUS = 10;

Engine::Engine(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight), state(INPUT), fovRadius(FOV_RADIUS), mouseCellX(0), mouseCellY(0) {
    TCODConsole::initRoot(screenWidth, screenHeight, "kek", false);
    player = new Entity(0, 0, '@', TCODColor::white, "Hero", true);
    player->controller = new PlayerController(player);
    player->being = new Being(
        player,
        1, // lvl,
        50, // baseHp,
        50, // baseStamina,
        10, // strength,
        10, // health,
        10, // agility,
        10, // endurance
        1
    );
    player->being->updateHp(player->being->getMaxHp());
    player->being->updateStamina(player->being->getMaxStamina());
    map = MapGenerator::generate(1, 90, 62);
    map->enter(player);
    gui = new GUI();
    computeFOV();
    actions = new ActionQueue();
    // initialize actions
    for(Entity** iter = map->entities.begin(); iter != map->entities.end(); iter++) {
        Entity* entity = *iter;
        entity->update();
    }
}

Engine::~Engine() {
    delete map;
    delete actions;
    delete gui;
}

void Engine::start() {
    while (!TCODConsole::isWindowClosed()) {
        update();
        render();
    }
}

void Engine::update() {
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, &mouse);

    static const int CELL_WIDTH = 12;
    static const int CELL_HEIGHT = 16;
    mouseCellX = mouse.x / CELL_WIDTH;
    mouseCellY = mouse.y / CELL_HEIGHT;

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
    delete action;
}

void Engine::render() {
    renderMap();
    renderEntities();
    gui->render();
    TCODConsole::flush();
}

void Engine::renderMap() {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            Tile* tile = map->getTile(x, y);
            if (isInFOV(x, y)) {
                TCODConsole::root->putCharEx(x, y, tile->ch, tile->frontColor, tile->backColor);
            } else if (isExplored(x, y)) {
                TCODConsole::root->putCharEx(x, y, tile->ch, tile->frontColorFaded, tile->backColorFaded);
            }
        }
    }
}

void Engine::renderEntities() {
    for (Entity** iter = map->entities.begin(); iter != map->entities.end(); iter++) {
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
    if (x < 0 || x >= map->width || y < 0 || y >= map->height) {
        return false;
    }
    if (map->walkMap->isInFov(x, y)) {
        map->tiles[x + y * map->width].explored = true;
        return true;
    }
    return false;
}

/**
 * @returns possibly NULL
 */
Entity* Engine::getAliveEntityByCoord(int x, int y) {
    for (Entity** iter = map->entities.begin(); iter != map->entities.end(); iter++) {
        Entity* entity = *iter;
        if (entity->isAlive() && entity->x == x && entity->y == y) {
            return entity;
        }
    }
    return NULL;
}
