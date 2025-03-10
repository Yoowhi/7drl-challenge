#pragma once
#include "libtcod.hpp"
#include "Ctrl.hpp"
#include <string>

class GUI {
    public:
        static const int GUI_WIDTH = 30;

        GUI();
        ~GUI();
        void render();
        void message(const tcod::ColorRGB &col, std::string text);

    private:
        tcod::Console* console = nullptr;
        struct Message {
            std::string text;
            tcod::ColorRGB color;
            Message(std::string text, const tcod::ColorRGB& col);
            ~Message();
        };
        TCODList<Message*> messages;
        void renderBorders();
        void renderBars();
        void renderStats();
        void renderEquipment();
        void renderInventory();
        void renderMessages();

        void renderMouseLook();
        void renderDebug();

        //void drawRect(int x, int y, int w, int h, tcod::ColorRGB& color);
        void drawStat(int x, int y, int w, std::string onLeft, std::string onRight);
        void drawBar(
            int x, int y,
            int width,
            float value,
            float maxValue,
            const tcod::ColorRGB& barColor,
            const tcod::ColorRGB& backColor
        );
        SDL_Keycode itemNumberToKeycode(int i);
};
