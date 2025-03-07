#pragma once
#include "libtcod.hpp"

class GUI {
    public:
        GUI();
        ~GUI();
        void render();
        void message(const TCODColor &col, const char *text, ...);

    private:
        TCODConsole* console;
        struct Message {
            char* text;
            TCODColor col;
            Message(const char* text, const TCODColor& col);
            ~Message();
        };
        TCODList<Message*> messages;
        void renderBar(
            int x, int y,
            int width,
            float value,
            float maxValue,
            const TCODColor& barColor,
            const TCODColor& backColor
        );
        void renderMouseLook();
};
