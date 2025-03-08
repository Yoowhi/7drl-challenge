#pragma once
class Entity;

class Controller {
    public:
        Entity* owner = nullptr;

        Controller(Entity* owner);
        virtual void update() = 0;
};
