#include "GUI.hpp"
#include "Engine.hpp"
#include "Entity.hpp"
#include "Being.hpp"
#include "Container.hpp"
#include "Item.hpp"
#include "Equipment.hpp"
#include "items/EquipmentItem.hpp"
#include "Map.hpp"
#include "colors.h"
#include "utility.hpp"
#include <cmath>

static const tcod::ColorRGB BACKGROUND_COLOR = Color::darkestGrey;
static const tcod::ColorRGB BORDER_COLOR = Color::darkerGrey;
static const tcod::ColorRGB KEY_COLOR = Color::green;

static const tcod::ColorRGB HEALTH_COLOR = Color::darkRed;
static const tcod::ColorRGB HEALTH_BACKGROUND_COLOR = Color::darkerRed;
static const tcod::ColorRGB STAMINA_COLOR = Color::darkGreen;
static const tcod::ColorRGB STAMINA_BACKGROUND_COLOR = Color::darkerGreen;
static const tcod::ColorRGB XP_COLOR = Color::darkSky;
static const tcod::ColorRGB XP_BACKGROUND_COLOR = Color::darkerSky;

static const int BARS_HEIGHT = 5;
static const int STATS_HEIGHT = 10;
static const int EQUIPMENT_HEIGHT = 10;
static const int INVENTORY_HEIGHT = Container::CONTAINER_SIZE + 2;

static const int BARS_Y = 1;
static const int STATS_Y = BARS_Y + BARS_HEIGHT + 1;
static const int EQUIPMENT_Y = STATS_Y + STATS_HEIGHT + 1;
static const int INVENTORY_Y = EQUIPMENT_Y + EQUIPMENT_HEIGHT + 1;
static const int MESSAGES_Y = INVENTORY_Y + INVENTORY_HEIGHT + 1;

//static const int MESSAGES_HEIGHT = 0;


// static const int EQUIPMENT_X = BAR_WIDTH + 2 + 1;
// static const int INVENTORY_X = EQUIPMENT_X + 34;
// static const int MSG_X = INVENTORY_X + 28;
// static const int MSG_HEIGHT = GUI::PANEL_HEIGHT - 1;

GUI::GUI() {
    console = new tcod::Console{GUI_WIDTH, engine->screenHeightCells};
}

GUI::~GUI() {
    delete console;
    messages.clearAndDelete();
}

GUI::Message::Message(std::string text, const tcod::ColorRGB& color) : text(text), color(color) {}

GUI::Message::~Message() {}

void GUI::render() {
    TCOD_console_set_default_background(console->get(), BACKGROUND_COLOR);
    TCOD_console_clear(console->get());

    renderBorders();
    renderBars();
    renderStats();
    renderEquipment();
    renderInventory();
    renderMessages();


    renderMouseLook();
    //renderDebug();

    tcod::blit(*engine->console->get(), *console->get(), {engine->screenWidthCells - GUI_WIDTH, 0});
}

void GUI::renderBorders() {
    tcod::draw_rect(*console->get(), {0, 0, GUI_WIDTH, 1}, 0, std::nullopt, BORDER_COLOR, TCOD_BKGND_SET);
    tcod::draw_rect(*console->get(), {0, STATS_Y - 1, GUI_WIDTH, 1}, 0, std::nullopt, BORDER_COLOR, TCOD_BKGND_SET);
    tcod::draw_rect(*console->get(), {0, EQUIPMENT_Y - 1, GUI_WIDTH, 1}, 0, std::nullopt, BORDER_COLOR, TCOD_BKGND_SET);
    tcod::draw_rect(*console->get(), {0, INVENTORY_Y - 1, GUI_WIDTH, 1}, 0, std::nullopt, BORDER_COLOR, TCOD_BKGND_SET);
    tcod::draw_rect(*console->get(), {0, MESSAGES_Y - 1, GUI_WIDTH, 1}, 0, std::nullopt, BORDER_COLOR, TCOD_BKGND_SET);
    tcod::draw_rect(*console->get(), {0, engine->screenHeightCells - 1, GUI_WIDTH, 1}, 0, std::nullopt, BORDER_COLOR, TCOD_BKGND_SET);
    tcod::draw_rect(*console->get(), {0, 0, 1, engine->screenHeightCells}, 0, std::nullopt, BORDER_COLOR, TCOD_BKGND_SET);
}

void GUI::renderBars(){
    drawBar(2, BARS_Y + 1, GUI_WIDTH - 3, (int)engine->player->being->hp, (int)engine->player->being->getMaxHp(), Color::darkRed, Color::darkestRed);
    drawBar(2, BARS_Y + 3, GUI_WIDTH - 3, (int)engine->player->being->stamina, (int)engine->player->being->getMaxStamina(), Color::darkGreen, Color::darkestGreen);
}

void GUI::renderStats(){
    drawStat(2, STATS_Y + 1, GUI_WIDTH - 6, "STRENGTH", tcod::stringf("%u", engine->player->being->strength));
    drawStat(2, STATS_Y + 2, GUI_WIDTH - 6, "HEALTH", tcod::stringf("%u", engine->player->being->health));
    drawStat(2, STATS_Y + 3, GUI_WIDTH - 6, "AGILITY", tcod::stringf("%u", engine->player->being->agility));
    drawStat(2, STATS_Y + 4, GUI_WIDTH - 6, "ENDURANCE", tcod::stringf("%u", engine->player->being->endurance));
    drawStat(2, STATS_Y + 6, GUI_WIDTH - 4, tcod::stringf("LVL: %u", engine->player->being->lvl), tcod::stringf("DEPTH: %u", engine->currentMapId + 1));
    tcod::print(*console->get(), {2, STATS_Y + 8}, tcod::stringf("XP"), Color::white, std::nullopt);
    drawBar(5, STATS_Y + 8, GUI_WIDTH - 6, engine->player->being->xp, engine->player->being->getMaxXp(), Color::darkSky, Color::darkestSky);
}

void GUI::renderEquipment() {
    Equipment& equipment = engine->player->being->equipment;

    EquipmentItem* weapon = equipment.getItem(EquipmentItem::WEAPON);
    if (weapon) {
        drawStat(2, EQUIPMENT_Y + 1, GUI_WIDTH - 4, tcod::stringf("WEAPON - %s", weapon->owner->name), weapon->getPrintMainStat(engine->player->being));
    } else {
        tcod::print(*console->get(), {2, EQUIPMENT_Y + 1}, tcod::stringf("WEAPON - "), Color::white, std::nullopt);
    }

    EquipmentItem* head = equipment.getItem(EquipmentItem::HELMET);
    if (head) {
        drawStat(2, EQUIPMENT_Y + 2, GUI_WIDTH - 4, tcod::stringf("HEAD   - %s", head->owner->name), head->getPrintMainStat(engine->player->being));
    } else {
        tcod::print(*console->get(), {2, EQUIPMENT_Y + 2}, tcod::stringf("HEAD   - "), Color::white, std::nullopt);
    }

    EquipmentItem* chest = equipment.getItem(EquipmentItem::CHEST);
    if (chest) {
        drawStat(2, EQUIPMENT_Y + 3, GUI_WIDTH - 4, tcod::stringf("CHEST  - %s", chest->owner->name), chest->getPrintMainStat(engine->player->being));
    } else {
        tcod::print(*console->get(), {2, EQUIPMENT_Y + 3}, tcod::stringf("CHEST  - "), Color::white, std::nullopt);
    }

    EquipmentItem* gloves = equipment.getItem(EquipmentItem::GLOVES);
    if (gloves) {
        drawStat(2, EQUIPMENT_Y + 4, GUI_WIDTH - 4, tcod::stringf("GLOVES - %s", gloves->owner->name), gloves->getPrintMainStat(engine->player->being));
    } else {
        tcod::print(*console->get(), {2, EQUIPMENT_Y + 4}, tcod::stringf("GLOVES - "), Color::white, std::nullopt);
    }

    EquipmentItem* boots = equipment.getItem(EquipmentItem::BOOTS);
    if (boots) {
        drawStat(2, EQUIPMENT_Y + 5, GUI_WIDTH - 3, tcod::stringf("BOOTS  - %s", boots->owner->name), boots->getPrintMainStat(engine->player->being));
    } else {
        tcod::print(*console->get(), {2, EQUIPMENT_Y + 5}, tcod::stringf("BOOTS  - "), Color::white, std::nullopt);
    }

    drawStat(2, EQUIPMENT_Y + 7, GUI_WIDTH - 4, "DEFENSE: ", tcod::stringf("%d", engine->player->being->getDefense()));
    std::string dmgString;
    if (weapon) {
        dmgString = weapon->getPrintMainStat(engine->player->being);
    } else {
        int minDamage, maxDamage;
        float mult = engine->player->being->getDamageMultiplier();
        minDamage = engine->player->being->getMinHandDamage() * mult;
        maxDamage = engine->player->being->getMaxHandDamage() * mult;
        dmgString = tcod::stringf("%d-%d", minDamage, maxDamage);
    }
    drawStat(2, EQUIPMENT_Y + 8, GUI_WIDTH - 4, "ATTACK: ", dmgString);
}

void GUI::renderInventory() {
    for (int i = 0; i < Container::CONTAINER_SIZE; i++) {
        Item* item = engine->player->inventory->items[i];
        if (item) {
            auto& tile = console->at({2, INVENTORY_Y + 1 + i});
            tile.ch = itemNumberToKeycode(i);
            tile.fg = KEY_COLOR;
            drawStat(4, INVENTORY_Y + 1 + i, GUI_WIDTH - 6, tcod::stringf(item->owner->name), item->getPrintMainStat(engine->player->being));
        }
    }
}

SDL_Keycode GUI::itemNumberToKeycode(int i) {
    switch (i) {
        case 0: return SDL_GetKeyFromScancode(Ctrl::USE0);
        case 1: return SDL_GetKeyFromScancode(Ctrl::USE1);
        case 2: return SDL_GetKeyFromScancode(Ctrl::USE2);
        case 3: return SDL_GetKeyFromScancode(Ctrl::USE3);
        case 4: return SDL_GetKeyFromScancode(Ctrl::USE4);
        default: throw "Too high item index in GUI::itemNumberToKeycode";
    }
}



void GUI::renderMessages() {
    int y = 0;
    bool isFilled = false;
    int MESSAGES_HEIGHT = engine->screenHeightCells - MESSAGES_Y;
    float colorCoef = 1.0f;
    float colorStep = colorCoef / (MESSAGES_HEIGHT);
    for (Message** iterator = messages.begin(); iterator != messages.end(); iterator++) {
        Message* message = *iterator;
        int rows = (int)ceilf((float)message->text.size() / (float)(GUI_WIDTH - 1));
        if (y + rows >= MESSAGES_HEIGHT) {
            rows = y + rows - MESSAGES_HEIGHT;
            isFilled = true;
            if (rows == 0) {
                return;
            }
        }
        tcod::print_rect(*console->get(), {1, MESSAGES_Y + y, GUI_WIDTH - 1, rows}, message->text, message->color, std::nullopt);
        y += rows;
        if ( colorCoef > colorStep ) {
            colorCoef -= colorStep;
        }
    }
}

void GUI::renderDebug() {

    // console->setDefaultForeground(Color::white);
    // console->print(0, 7, "%u", TCODSystem::getFps());
    // console->print(6, 7, "%u:%u", engine->controls_mouseCellX, engine->controls_mouseCellY);
    // console->print(16, 7, "%u:%u", engine->controls_mouseCellX, engine->controls_mouseCellY);
    // int windowWidth, windowHeight;
    // TCODSystem::getCurrentResolution(&windowWidth, &windowHeight);
    // console->print(26, 7, "%u:%u", windowWidth, windowHeight);
}

void debugString(std::string str, int x) {
    tcod::print(*engine->console->get(), {x, 0}, str, Color::green, Color::black);
}

void GUI::message(const tcod::ColorRGB &color, std::string text) {
    // https://www.roguebasin.com/index.php/Complete_roguelike_tutorial_using_C%2B%2B_and_libtcod_-_part_7:_the_GUI#:~:text=maxValue)%3B%0A%7D-,The%20message%20log,-We%20want%20a
    int MESSAGES_HEIGHT = engine->screenHeightCells - MESSAGES_Y;
    if (messages.size() >= MESSAGES_HEIGHT) {
        Message* toRemove = messages.pop();
        delete toRemove;
    }
    Message* msg = new Message(text, color);
    messages.insertBefore(msg, 0);
}

void GUI::renderMouseLook() {
    if (!engine->isInFOV(engine->input.mouseCellX, engine->input.mouseCellY)) {
        return;
    }
    std::string names;
    bool first = true;
    for (Entity** it = engine->map->entities.begin(); it != engine->map->entities.end(); it++) {
        Entity* entity = *it;
        if (entity->x == engine->input.mouseCellX && entity->y == engine->input.mouseCellY ) {
            if (!first) {
                names += ", ";
            }
            names += entity->name;
            first = false;
        }
    }
    tcod::print(*console->get(), {0, 0}, names, std::nullopt, std::nullopt);
}


// void GUI::drawRect(int x, int y, int w, int h, tcod::ColorRGB& color) {
//     for (int pointY = y; pointY < y + h; pointY++) {
//         for (int pointX = x; pointX < x + w; pointX++) {
//             auto& tile = console->at({x, y});
//             tile.bg = color;
//         }
//     }
// }

void GUI::drawBar(
    int x, int y,
    int width,
    float value,
    float maxValue,
    const tcod::ColorRGB& barColor,
    const tcod::ColorRGB& backColor
) {
    tcod::draw_rect(*console->get(), {x, y, width, 1}, 0, std::nullopt, backColor, TCOD_BKGND_SET);
    int barWidth = (int)(value / maxValue * width);
    if (barWidth > 0) {
        tcod::draw_rect(*console->get(), {x, y, barWidth, 1}, 0, std::nullopt, barColor, TCOD_BKGND_SET);
    }
    if (value >= 0 && maxValue >= 0) {
        tcod::print_rect(*console->get(), {x, y, width, 1}, tcod::stringf("%g/%g", value, maxValue), Color::white,std::nullopt, TCOD_alignment_t::TCOD_CENTER);
    }
}

void GUI::drawStat(int x, int y, int w, std::string onLeft, std::string onRight) {
    tcod::print(*console->get(), {x, y}, onLeft, Color::white, std::nullopt);
    tcod::print(*console->get(), {x + w, y}, onRight, Color::white, std::nullopt, TCOD_alignment_t::TCOD_RIGHT);
}
