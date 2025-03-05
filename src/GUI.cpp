#include "libtcod.hpp"
#include "Controller.hpp"
#include "Being.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "Action.hpp"
#include "ActionQueue.hpp"
#include "Engine.hpp"
#include "GUI.hpp"

static const int PANEL_HEIGHT = 8;
static const int BAR_WIDTH = 20;
static const int MSG_X = 50;
static const int MSG_HEIGHT = PANEL_HEIGHT - 1;

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
    console->setDefaultBackground(TCODColor::black);

    renderBar(1, 2, BAR_WIDTH, (int)engine.player->being->hp, (int)engine.player->being->getMaxHp(), TCODColor::darkRed, TCODColor::darkestRed);
    renderBar(1, 4, BAR_WIDTH, (int)engine.player->being->stamina, (int)engine.player->being->getMaxStamina(), TCODColor::darkGreen, TCODColor::darkestGreen);
    renderBar(1, 6, BAR_WIDTH, engine.player->being->xp, engine.player->being->getMaxXp(), TCODColor::darkSky, TCODColor::darkestSky);
    int y = 1;
    float colorCoef = 1.0f;
    for (Message** iterator = messages.begin(); iterator != messages.end(); iterator++) {
        Message* message = *iterator;
        console->setDefaultForeground(message->col * colorCoef);
        console->print(MSG_X, y, message->text);
        y++;
        if ( colorCoef > 0.3f ) {
            colorCoef -= 0.1f;
        }
    }
    renderMouseLook();
    TCODConsole::blit(console, 0, 0, engine.screenWidth, PANEL_HEIGHT, TCODConsole::root, 0, engine.screenHeight - PANEL_HEIGHT);
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
