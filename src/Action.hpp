#pragma once
class Entity;

class Action {
    public:
        Entity* actor = nullptr;
        int time;
        int timeLeft;

        Action(Entity* actor, int time);
        virtual void execute() = 0;
};
