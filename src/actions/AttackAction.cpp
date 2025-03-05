#include "libtcod.hpp"
#include <stdexcept>
#include "../Controller.hpp"
#include "../Being.hpp"
#include "../Action.hpp"
#include "../Entity.hpp"
#include "../Map.hpp"
#include "../ActionQueue.hpp"
#include "../GUI.hpp"
#include "../Engine.hpp"
#include "AttackAction.hpp"

AttackAction::AttackAction(Entity* actor, int x, int y) : Action(actor, 100) {
    this->x = x;
    this->y = y;
}

void AttackAction::execute() {
    Entity* target = engine.getAliveEntityByCoord(x, y);
    if (!target) {
        engine.gui->message(TCODColor::white, "%s missed", actor->name);
        return;
    }
    // damage calculation
    float defence = getTargetDefence(target);
    float staminaCost = getStaminaCost(actor);
    float damage = getAttackerDamage(actor, staminaCost);
    float resultingDamage = damage - defence;
    if (resultingDamage < 0) {
        resultingDamage = 0;
    }
    // damage applying
    engine.gui->message(TCODColor::white, "%s deals %s %u damage", actor->name, target->name, (int)resultingDamage);
    target->being->updateHp(-resultingDamage);
    if (!target->isAlive()) {
        actor->being->addXp(target->being->getXpForKill());
    }
    actor->being->updateStamina(-staminaCost);
}

int AttackAction::getTargetDefence(Entity* target) {
    return 0;
}

float AttackAction::getStaminaCost(Entity* attacker) {
    return 8.0f;
}

float AttackAction::getAttackerDamage(Entity* attacker, float staminaCost) {
    float dmg = 5.0f * attacker->being->getDamageMultiplier();
    float currentStamina = attacker->being->stamina;
    if (staminaCost > currentStamina) {
        // ratio
        dmg *= currentStamina / staminaCost;
    }
    return dmg;
}
