#include "libtcod.hpp"
#include "AttackAction.hpp"
#include "../Engine.hpp"
#include "../items/EquipmentItem.hpp"
#include "../GUI.hpp"
#include "../Entity.hpp"
#include "../Being.hpp"
#include "../colors.h"

AttackAction::AttackAction(Entity* actor, int x, int y) : Action(actor, 100), x(x), y(y) {}

void AttackAction::execute() {
    Entity* target = engine->getAliveEntityByCoord(x, y);
    if (!target) {
        engine->gui->message(Color::white, tcod::stringf("%s missed", actor->name));
        return;
    }
    // damage calculation
    float defense = getTargetDefence(target);
    float staminaCost = getStaminaCost(actor);
    float damage = getAttackerDamage(actor, staminaCost);
    float resultingDamage = damage - defense;
    if (resultingDamage < 0) {
        resultingDamage = 0;
    }
    // damage applying
    engine->gui->message(Color::white, tcod::stringf("%s deals %s %u damage", actor->name, target->name, (int)resultingDamage));
    target->being->updateHp(-resultingDamage);
    if (!target->isAlive()) {
        actor->being->addXp(target->being->getXpForKill());
    }
    actor->being->updateStamina(-staminaCost);
}

int AttackAction::getTargetDefence(Entity* target) {
    return target->being->getDefense();
}

float AttackAction::getStaminaCost(Entity* attacker) {
    float cost = 1.0f;
    EquipmentItem* weapon = attacker->being->equipment.getItem(EquipmentItem::WEAPON);
    if (weapon) {
        cost = weapon->weight;
    }
    return cost;
}

float AttackAction::getAttackerDamage(Entity* attacker, float staminaCost) {
    float minDmg = attacker->being->getMinHandDamage();
    float maxDmg = attacker->being->getMaxHandDamage();
    EquipmentItem* weapon = attacker->being->equipment.getItem(EquipmentItem::WEAPON);
    if (weapon) {
        minDmg = weapon->minDamage;
        maxDmg = weapon->maxDamage;
    }
    TCODRandom* rng = TCODRandom::getInstance();
    int initialDmg = rng->getFloat(minDmg, maxDmg);
    float dmg = initialDmg * attacker->being->getDamageMultiplier();
    float currentStamina = attacker->being->stamina;
    if (staminaCost > currentStamina) {
        // ratio
        dmg *= currentStamina / staminaCost;
    }
    return dmg;
}
