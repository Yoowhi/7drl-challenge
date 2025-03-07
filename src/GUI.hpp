#pragma once
#include "libtcod.hpp"
#include "Ctrl.hpp"

class GUI {
    public:
        static const int PANEL_HEIGHT = 8;

        GUI();
        ~GUI();
        void render();
        void message(const TCODColor &col, const char *text, ...);

    private:
        TCODConsole* console;
        struct Message {
            char* text = nullptr;
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
        void renderMessages();
        void renderInventory();
        void renderEquipment();
        void renderDebug();
        Ctrl itemNumberToCtrl(int i);
};
