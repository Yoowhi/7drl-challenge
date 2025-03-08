#pragma once
#include "Controller.hpp"
class Entity;
class Action;

class PlayerController : public Controller {
    public:
        PlayerController(Entity* owner);
        ~PlayerController();
        void update();

    private:
        Action* moveOrAttack(int dx, int dy);
        Action* handleChar(char& ascii);
        Action* handleActivate();
        Action* useFromInventory(int id);
        Action* dropFromInventory(int id);
};
