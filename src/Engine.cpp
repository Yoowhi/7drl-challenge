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
#include "colors.h"
#include "libtcod/timer.hpp"

static const int FOV_RADIUS = 10;

Engine::Engine(int screenWidthCells, int screenHeightCells, tcod::Console* console, tcod::Context* context) : screenWidthCells(screenWidthCells), screenHeightCells(screenHeightCells), state(INPUT), fovRadius(FOV_RADIUS), currentMapId(0), console(console), context(context) {
}

Engine::~Engine() {
    delete map;
    delete actions;
    delete gui;
    delete console;
}

int fps = 20;
auto timer = tcod::Timer();

void Engine::start() {
    gui = new GUI();
    player = CreatureFactory::newPlayer();
    toNextMap();
    while (1 < 2) {
        uint32_t currentTimeMs = SDL_GetTicks();
        float currentTime = static_cast<float>(currentTimeMs) / 1000.f;
        float deltaTime = timer.sync(fps);
        while (SDL_PollEvent(&event)) {
            context->convert_event_coordinates(event);
            switch (event.type)
            {
                case SDL_QUIT:
                    return;
                case SDL_MOUSEMOTION:
                    context->convert_event_coordinates(event);
                    input.mouseCellX = event.motion.x;
                    input.mouseCellY = event.motion.y;
                    break;
                case SDL_KEYDOWN:
                // сохранять сканкоды, в GUI воспользоваться функцией конвертации в кейкод
                    input.anyKeyPressed = true;
                    input.keysPressed[event.key.keysym.scancode] = true;
                    if (event.key.keysym.sym == SDLK_LSHIFT) {
                        input.shift = true;
                    }
                    input.lastKey = event.key.keysym.scancode;
                    break;
                case SDL_KEYUP:
                input.anyKeyPressed = false;
                input.keysPressed[event.key.keysym.scancode] = false;
                    if (event.key.keysym.sym == SDLK_LSHIFT) {
                        input.shift = false;
                    }
                    break;
                default:
                    break;
            }
        }
        update();
        render();
    }
}

void Engine::update() {
    if (state == INPUT) {
        player->update();
        return;
    }
    while (state != INPUT) {
        if (state == UPSTAIRS) {
            toPreviousMap();
            state = INPUT;
        }
        if (state == DOWNSTAIRS) {
            toNextMap();
            state = INPUT;
        }
        Action* action = actions->next();
        if (!action) {
            return;
        }
        action->execute();
        if (action->actor == player) {
            computeFOV();
            if (state != UPSTAIRS && state != DOWNSTAIRS) {
                state = INPUT;
            }
        } else {
            action->actor->update();
        }
        delete action;
    }
}

void Engine::render() {
    TCOD_console_clear(console->get());
    renderMap();
    renderEntities();
    gui->render();
    context->present(*console);
}

void Engine::renderMap() {
    for (int y = 0; y < map->height; ++y) {
        for (int x = 0; x < map->width; ++x) {
            Tile* mapTile = map->getTile(x, y);
            if (!mapTile) {
                continue;
            }
            auto& tile = console->at({x, y});
            bool inFOV = isInFOV(x, y);
            tile.ch = mapTile->ch;
            tile.bg = inFOV ? mapTile->backColor : mapTile->explored ? mapTile->backColorFaded : Color::black;
            tile.fg = inFOV ? mapTile->frontColor : mapTile->explored ? mapTile->frontColorFaded : Color::black;
        }
    }
}

void Engine::renderEntities() {
    for (Entity** iter = map->entities.begin(); iter != map->entities.end(); iter++) {
        Entity* entity = *iter;
        if (entity != player && isInFOV(entity->x, entity->y)) {
            auto& tile = console->at({entity->x, entity->y});
            tile.ch = entity->symbol;
            tile.fg = entity->color;
        }
    }
    // render player above everything else
    auto& tile = console->at({player->x, player->y});
    tile.ch = player->symbol;
    tile.fg = player->color;
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
    if (maps.size() == currentMapId) {
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
        gui->message(Color::purple, "Coward!");
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
    return map = MapGenerator::generate(lvl, screenWidthCells - GUI::GUI_WIDTH, screenHeightCells);
}

bool Engine::isCharacterKey(SDL_Keycode keycode) {
    // Check if the keycode corresponds to a printable ASCII character
    return (keycode >= SDLK_SPACE && keycode <= SDLK_z);
}
