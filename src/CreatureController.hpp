#pragma once
#include "Controller.hpp"
class Entity;

class CreatureController : public Controller {
    public:
        CreatureController(Entity* owner);
        ~CreatureController();
        void update();
};
