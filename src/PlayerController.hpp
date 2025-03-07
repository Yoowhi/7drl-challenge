#pragma once
#include "Controller.hpp"
class Entity;

class PlayerController : public Controller {
    public:
        PlayerController(Entity* owner);
        ~PlayerController();
        void update();
};
