#include "GUI.hpp"
#include "Engine.hpp"
#include "Entity.hpp"
#include "Being.hpp"
#include "Container.hpp"
#include "Item.hpp"
#include "Equipment.hpp"
#include "items/EquipmentItem.hpp"
#include "Map.hpp"

static const int BAR_WIDTH = 20;
static const int EQUIPMENT_X = BAR_WIDTH + 2 + 1;
static const int INVENTORY_X = EQUIPMENT_X + 34;
static const int MSG_X = INVENTORY_X + 28;
static const int MSG_HEIGHT = GUI::PANEL_HEIGHT - 1;

GUI::GUI() {
    console = new TCODConsole(engine.screenWidth, PANEL_HEIGHT);
}

GUI::~GUI() {
    delete console;
    messages.clearAndDelete();
}

GUI::Message::Message(const char* text, const TCODColor& col) : col(col) {
    this->text = new char[strlen(text)];
    strcpy(this->text,text);
}

GUI::Message::~Message() {
    delete [] text;
}

void GUI::render() {
    console->setDefaultBackground(TCODColor::black);
    console->clear();

    console->setDefaultBackground(TCODColor::darkGrey);
    console->rect(0, 0, engine.screenWidth, 1, false, TCOD_BKGND_SET);
    console->rect(EQUIPMENT_X - 1, 0, 1, PANEL_HEIGHT, false, TCOD_BKGND_SET);
    console->rect(MSG_X - 1, 0, 1, PANEL_HEIGHT, false, TCOD_BKGND_SET);
    console->rect(INVENTORY_X - 1, 0, 1, PANEL_HEIGHT, false, TCOD_BKGND_SET);
    console->setDefaultBackground(TCODColor::black);

    renderBar(1, 2, BAR_WIDTH, (int)engine.player->being->hp, (int)engine.player->being->getMaxHp(), TCODColor::darkRed, TCODColor::darkestRed);
    renderBar(1, 4, BAR_WIDTH, (int)engine.player->being->stamina, (int)engine.player->being->getMaxStamina(), TCODColor::darkGreen, TCODColor::darkestGreen);
    renderBar(1, 6, BAR_WIDTH, engine.player->being->xp, engine.player->being->getMaxXp(), TCODColor::darkSky, TCODColor::darkestSky);
    renderMessages();
    renderMouseLook();
    renderInventory();
    renderEquipment();
    //renderDebug();
    TCODConsole::blit(console, 0, 0, engine.screenWidth, PANEL_HEIGHT, TCODConsole::root, 0, engine.screenHeight - PANEL_HEIGHT);
}

void GUI::renderInventory() {
    console->setDefaultForeground(TCODColor::darkestGrey);
    console->print(INVENTORY_X + 3, 0, "%c", engine.lastKey.shift ? "Inventory: DROP" : "Inventory: USE" );
    Container* container = engine.player->inventory;
    for (int i = 0; i < Container::CONTAINER_SIZE; i++) {
        Item* item = container->getItem(i);
        if (item) {
            console->setDefaultForeground(TCODColor::darkGreen);
            console->print(INVENTORY_X + 1, 2 + i, "%c", itemNumberToCtrl(i));
            console->setDefaultForeground(TCODColor::white);
            console->print(INVENTORY_X + 3, 2 + i, "%s", item->owner->name);
        }
    }
}

Ctrl GUI::itemNumberToCtrl(int i) {
    switch (i) {
        case 0: return Ctrl::USE0;
        case 1: return Ctrl::USE1;
        case 2: return Ctrl::USE2;
        case 3: return Ctrl::USE3;
        case 4: return Ctrl::USE4;
        case 5: return Ctrl::USE5;
        default: throw std::runtime_error("Too high item index in GUI::itemNumberToCtrl");
    }
}

void GUI::renderEquipment() {
    console->setDefaultForeground(TCODColor::white);
    Equipment& equipment = engine.player->being->equipment;
    EquipmentItem* weapon = equipment.getItem(EquipmentItem::WEAPON);
    if (weapon) {
        console->print(EQUIPMENT_X + 1, 2, "WEAPON: %s", weapon->owner->name);
    } else {
        console->print(EQUIPMENT_X + 1, 2, "WEAPON: -");
    }
    EquipmentItem* head = equipment.getItem(EquipmentItem::HELMET);
    if (head) {
        console->print(EQUIPMENT_X + 1, 3, "HEAD  : %s", head->owner->name);
    } else {
        console->print(EQUIPMENT_X + 1, 3, "HEAD  : -");
    }
    EquipmentItem* chest = equipment.getItem(EquipmentItem::CHEST);
    if (chest) {
        console->print(EQUIPMENT_X + 1, 4, "CHEST : %s", chest->owner->name);
    } else {
        console->print(EQUIPMENT_X + 1, 4, "CHEST : -");
    }
    EquipmentItem* gloves = equipment.getItem(EquipmentItem::GLOVES);
    if (gloves) {
        console->print(EQUIPMENT_X+ 1, 5, "GLOVES: %s", gloves->owner->name);
    } else {
        console->print(EQUIPMENT_X + 1, 5, "GLOVES: -");
    }
    EquipmentItem* boots = equipment.getItem(EquipmentItem::BOOTS);
    if (boots) {
        console->print(EQUIPMENT_X + 1, 6, "BOOTS : %s", boots->owner->name);
    } else {
        console->print(EQUIPMENT_X + 1, 6, "BOOTS : -");
    }
}

void GUI::renderMessages() {
    int y = 1;
    float colorCoef = 1.0f;
    for (Message** iterator = messages.begin(); iterator != messages.end(); iterator++) {
        Message* message = *iterator;
        console->setDefaultForeground(message->col * colorCoef);
        console->print(MSG_X, y, message->text);
        y++;
        if ( colorCoef > 0.2f ) {
            colorCoef -= 0.2f;
        }
    }
}

void GUI::renderDebug() {
    console->setDefaultForeground(TCODColor::white);
    console->print(0, 7, "%u", TCODSystem::getFps());
    console->print(6, 7, "%u:%u", engine.mouseCellX, engine.mouseCellY);
    console->print(16, 7, "%u:%u", engine.mouse.x, engine.mouse.y);
    int windowWidth, windowHeight;
    TCODSystem::getCurrentResolution(&windowWidth, &windowHeight);
    console->print(26, 7, "%u:%u", windowWidth, windowHeight);
}

void GUI::renderBar(
    int x, int y,
    int width,
    float value,
    float maxValue,
    const TCODColor& barColor,
    const TCODColor& backColor
) {
    console->setDefaultBackground(backColor);
    console->rect(x, y, width, 1, false, TCOD_BKGND_SET);
    int barWidth = (int)(value / maxValue * width);
    if (barWidth > 0) {
        console->setDefaultBackground(barColor);
        console->rect(x, y, barWidth, 1, false, TCOD_BKGND_SET);
    }
    console->setDefaultForeground(TCODColor::white);
    console->printEx(x + width / 2, y, TCOD_BKGND_NONE,TCOD_CENTER, "%g/%g", value, maxValue);
}

void GUI::message(const TCODColor &col, const char *text, ...) {
    // https://www.roguebasin.com/index.php/Complete_roguelike_tutorial_using_C%2B%2B_and_libtcod_-_part_7:_the_GUI#:~:text=maxValue)%3B%0A%7D-,The%20message%20log,-We%20want%20a
    va_list ap;
    char buf[128];
    va_start(ap,text);
    vsprintf(buf,text,ap);
    va_end(ap);

    char *lineBegin=buf;
    char *lineEnd;

    do {
        // make room for the new message
        if (messages.size() == MSG_HEIGHT) {
            Message* toRemove = messages.pop();
            delete toRemove;
        }
        lineEnd=strchr(lineBegin,'\n');
        if ( lineEnd ) {
            *lineEnd='\0';
        }
        Message *msg=new Message(lineBegin, col);
        messages.insertBefore(msg, 0);
        lineBegin = lineEnd + 1;
    } while (lineEnd);
}

void GUI::renderMouseLook() {
    if (!engine.isInFOV(engine.mouseCellX, engine.mouseCellY)) {
        return;
    }
    char buf[128]="";
    bool first=true;
    for (Entity** it = engine.map->entities.begin(); it != engine.map->entities.end(); it++) {
        Entity* entity = *it;
        if (entity->x == engine.mouseCellX && entity->y == engine.mouseCellY ) {
            if (!first) {
                strcat(buf, ", ");
            } else {
                first = false;
            }
            strcat(buf, entity->name);
        }
    }
    console->setDefaultForeground(TCODColor::white);
    console->print(1, 0, buf);
}
