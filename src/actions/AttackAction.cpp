#include "libtcod.hpp"
#include "AttackAction.hpp"
#include "../Engine.hpp"
#include "../items/WeaponItem.hpp"
#include "../GUI.hpp"
#include "../Entity.hpp"
#include "../Being.hpp"
#include "../colors.h"

AttackAction::AttackAction(Entity* actor, int x, int y) : Action(actor, 100), x(x), y(y) {
    weapon = (WeaponItem*)actor->being->equipment.getItem(EquipmentItem::WEAPON);
    float mult = this->actor->being->getTimeMultiplier();
    this->time = (int)((float)this->time * mult);
    this->timeLeft = this->time;
}

void AttackAction::execute() {
    Entity* target = engine->getAliveEntityByCoord(x, y);
    if (!target) {
        engine->gui->message(Color::white, tcod::stringf("%s missed", actor->name));
        return;
    }
    float defense = getTargetDefence(target);
    float staminaCost = getStaminaCost(actor);
    float damage = getAttackerDamage(actor, staminaCost);
    float hpDamage = damage - defense;
    engine->gui->message(Color::white, tcod::stringf("%s deals %s %u damage", actor->name, target->name, (int)damage));
    target->being->updateDefense(-damage);
    if (hpDamage > 0) {
        target->being->updateHp(-hpDamage);
    }
    if (!target->isAlive()) {
        actor->being->addXp(target->being->getXpForKill());
    }
    actor->being->updateStamina(-staminaCost);
}

int AttackAction::getTargetDefence(Entity* target) {
    return target->being->getMaxDefense();
}

float AttackAction::getStaminaCost(Entity* attacker) {
    return weapon->weight;
}

float AttackAction::getAttackerDamage(Entity* attacker, float staminaCost) {
    TCODRandom* rng = TCODRandom::getInstance();
    float initialDmg = rng->getFloat(weapon->getMinDamage(), weapon->getMaxDamage());
    float dmg = initialDmg * attacker->being->getDamageMultiplier();
    float currentStamina = attacker->being->stamina;
    if (staminaCost > currentStamina) {
        // ratio
        dmg *= currentStamina / staminaCost;
    }
    return dmg;
}
