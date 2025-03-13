#include "WeaponItem.hpp"
#include "libtcod.hpp"
#include "../Being.hpp"

WeaponItem::WeaponItem(Entity* owner, int weight, float minDamage, float maxDamage, int attackSpeed) : EquipmentItem(owner, EquipmentItem::WEAPON, weight), minDamage(minDamage), maxDamage(maxDamage), attackSpeed(attackSpeed) {}

std::string WeaponItem::getPrintStats(Being* being) {
    float mult = being->getDamageMultiplier();
    return tcod::stringf("%u-%u", (int)(minDamage * mult), (int)(maxDamage * mult));
}

float WeaponItem::getMinDamage() {
    return minDamage;
}

float WeaponItem::getMaxDamage() {
    return maxDamage;
}

int WeaponItem::getAttackSpeed() {
    return attackSpeed;
}
