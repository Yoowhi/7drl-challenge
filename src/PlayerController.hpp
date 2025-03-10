#pragma once
#include "Controller.hpp"
#include "SDL.h"
class Entity;
class Action;

class PlayerController : public Controller {
    public:
        PlayerController(Entity* owner);
        ~PlayerController();
        void update();

    private:
        Action* moveOrAttack(int dx, int dy);
        Action* handleScancode(SDL_Scancode keycode);
        Action* handleActivate();
        Action* useFromInventory(int id);
        Action* dropFromInventory(int id);
};
