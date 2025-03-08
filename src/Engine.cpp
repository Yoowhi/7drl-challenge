#include "Engine.hpp"
#include "PlayerController.hpp"
#include "Being.hpp"
#include "MapGenerator.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "ActionQueue.hpp"
#include "GUI.hpp"
#include "Action.hpp"
#include "CreatureFactory.hpp"


static const int FOV_RADIUS = 10;

Engine::Engine(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight), state(INPUT), fovRadius(FOV_RADIUS), mouseCellX(0), mouseCellY(0), currentMapId(-1) {
    TCODConsole::initRoot(screenWidth, screenHeight, "Endless Dungeon", false, TCOD_RENDERER_SDL);
    TCODConsole::setCustomFont("./data/tileset.png",TCOD_FONT_LAYOUT_ASCII_INROW, 16, 16);
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &lastKey, &mouse);
    //TCODSystem::setFps(25);
    gui = new GUI();
    player = CreatureFactory::newPlayer();
    toNextMap();
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
    int windowWidth, windowHeight;
    TCODSystem::getCurrentResolution(&windowWidth, &windowHeight);
    int cellWidth = windowWidth / screenWidth;
    int cellHeight = windowHeight / screenHeight;
    mouseCellX = mouse.x / cellWidth;
    mouseCellY = mouse.y / cellHeight;
    if (state == UPSTAIRS) {
        toPreviousMap();
        clearScreen();
        state = INPUT;
    }
    if (state == DOWNSTAIRS) {
        toNextMap();
        clearScreen();
        state = INPUT;
    }
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
        if (state != UPSTAIRS & state != DOWNSTAIRS) {
            state = INPUT;
        }
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

void Engine::clearScreen() {
    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            TCODConsole::root->setChar(x, y, ' ');
            TCODConsole::root->setCharBackground(x, y, TCODConsole::root->getDefaultBackground());
        }
    }
}

void Engine::renderEntities() {
    for (Entity** iter = map->entities.begin(); iter != map->entities.end(); iter++) {
        Entity* entity = *iter;
        if (entity != player && isInFOV(entity->x, entity->y)) {
            TCODConsole::root->setChar(entity->x, entity->y, entity->symbol);
            TCODConsole::root->setCharForeground(entity->x, entity->y, entity->color);
        }
    }
    // render player above everything else
    TCODConsole::root->setChar(player->x, player->y, player->symbol);
    TCODConsole::root->setCharForeground(player->x, player->y, player->color);
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
 * @returns possibly nullptr
 */
Entity* Engine::getAliveEntityByCoord(int x, int y) {
    for (Entity** iter = map->entities.begin(); iter != map->entities.end(); iter++) {
        Entity* entity = *iter;
        if (entity->isAlive() && entity->x == x && entity->y == y) {
            return entity;
        }
    }
    return nullptr;
}

/**
 * @returns possibly nullptr
 */
Entity* Engine::getItemEntityByCoord(int x, int y) {
    for (Entity** iter = map->entities.begin(); iter != map->entities.end(); iter++) {
        Entity* entity = *iter;
        if (entity->item && entity->x == x && entity->y == y) {
            return entity;
        }
    }
    return nullptr;
}

/**
 * @returns possibly nullptr
 */
Entity* Engine::getStairsEntityByCoord(int x, int y) {
    for (Entity** iter = map->entities.begin(); iter != map->entities.end(); iter++) {
        Entity* entity = *iter;
        if (entity->stairs && entity->x == x && entity->y == y) {
            return entity;
        }
    }
    return nullptr;
}

void Engine::toNextMap() {
    if (this->map) {
        this->map->exit(player);
    }
    Map* map = nullptr;
    if (maps.size() - 1 == currentMapId) {
        map = newMap(player->being->lvl);
        maps.push(map);
    } else {
        map = maps.get(currentMapId);
    }
    map->enterFromUp(player);
    currentMapId++;
    initMap(map);
}

void Engine::toPreviousMap() {
    this->map->exit(player);
    if (currentMapId == 0) {
        gui->message(TCODColor::purple, "Coward!");
        return;
    }
    currentMapId--;
    Map* map = maps.get(currentMapId);
    map->enterFromDown(player);
    initMap(map);
}

void Engine::initMap(Map* map) {
    if (actions) delete actions;
    actions = new ActionQueue();
    this->map = map;
    computeFOV();
    // initialize actions
    for(Entity** iter = this->map->entities.begin(); iter != this->map->entities.end(); iter++) {
        Entity* entity = *iter;
        entity->update();
    }
}

Map* Engine::newMap(int lvl) {
    return map = MapGenerator::generate(lvl, screenWidth, screenHeight - GUI::PANEL_HEIGHT);
}
