#pragma once
class Entity;

class Action {
    public:
        Entity* actor = nullptr;
        int time;
        int timeLeft;

        Action(Entity* actor, int time);
        virtual ~Action() = default;
        virtual void execute() = 0;
};
