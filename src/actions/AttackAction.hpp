#pragma once
#include "../Action.hpp"
#include "../Entity.hpp"
class Entity;

class AttackAction : public Action {
    public:
        int x, y;

        AttackAction(Entity* actor, int x, int y);
        void execute();

    private:
        int getTargetDefence(Entity* target);
        float getAttackerDamage(Entity* attacker, float staminaCost);
        float getStaminaCost(Entity* attacker);
};
