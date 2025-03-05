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

AttackAction::AttackAction(Entity* actor, int x, int y) : Action() {
    this->actor = actor;
    this->time = 50;
    this->timeLeft = 50;
    this->x = x;
    this->y = y;
}

void AttackAction::execute() {
    Entity* target = engine.getAliveEntityByCoord(x, y);
    if (!target) {
        engine.gui->message(TCODColor::white, "%s missed", actor->name);
        return;
    }
    int defence = getTargetDefence(target);
    int damage = getAttackerDamage(actor);
    // damage calculation
    int resultingDamage = damage - defence;
    if (resultingDamage < 0) {
        resultingDamage = 0;
    }
    // damage applying
    target->being->hp -= resultingDamage;
    engine.gui->message(TCODColor::white, "%s deals %s %u damage", actor->name, target->name, resultingDamage);
    if (target->being->hp <= 0) {
        target->being->hp = 0;
        target->being->die();
    }
}

int AttackAction::getTargetDefence(Entity* target) {
    return target->being->defence;
}

int AttackAction::getAttackerDamage(Entity* attacker) {
    return 5;
}
