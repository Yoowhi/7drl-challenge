#include "HandsWeaponItem.hpp"
#include "libtcod.hpp"
#include "../Being.hpp"

HandsWeaponItem::HandsWeaponItem(Entity* owner, Being* being) : WeaponItem(owner, 0, 0.0f, 0.0f, 0), being(being) {}

std::string HandsWeaponItem::getPrintStats(Being* being) {
    float mult = being->getDamageMultiplier();
    return tcod::stringf("%u-%u", (int)(getMinDamage() * mult), (int)(getMaxDamage() * mult));
}

float HandsWeaponItem::getMinDamage() {
    return 0.0f;
}

float HandsWeaponItem::getMaxDamage() {
    return 2.0f;
}

int HandsWeaponItem::getAttackSpeed() {
    return 60;
}
