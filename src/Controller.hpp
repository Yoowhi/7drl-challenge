#pragma once
class Entity;

class Controller {
    public:
        Entity* owner;

        Controller(Entity* owner);
        ~Controller();
        virtual void update() = 0;
};
