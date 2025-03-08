#pragma once
class Entity;

class Controller {
    public:
        Entity* owner = nullptr;

        Controller(Entity* owner);
        ~Controller();
        virtual void update() = 0;
};
