#include "libtcod.hpp"
#include "AttackAction.hpp"
#include "../Engine.hpp"
#include "../items/EquipmentItem.hpp"
#include "../GUI.hpp"
#include "../Entity.hpp"
#include "../Being.hpp"

AttackAction::AttackAction(Entity* actor, int x, int y) : Action(actor, 100), x(x), y(y) {}

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
    float cost = 1.0f;
    EquipmentItem* weapon = attacker->being->equipment.getItem(EquipmentItem::WEAPON);
    if (weapon) {
        cost = weapon->weight;
    }
}

float AttackAction::getAttackerDamage(Entity* attacker, float staminaCost) {
    EquipmentItem* weapon = attacker->being->equipment.getItem(EquipmentItem::WEAPON);
    float minDmg = 0;
    float maxDmg = 1;
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
