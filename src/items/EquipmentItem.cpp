#include "EquipmentItem.hpp"
#include "../actions/EquipAction.hpp"
#include "libtcod.hpp"
#include "../Being.hpp"

EquipmentItem::EquipmentItem(Entity* owner, Type type) : Item(owner), type(type)  {}

Action* EquipmentItem::use(Entity* user) {
    return new EquipAction(user, this);
}

std::string EquipmentItem::getPrintMainStat(Being* being) {
    if (type == WEAPON) {
        float mult = being->getDamageMultiplier();
        return tcod::stringf("%u-%u", (int)(minDamage * mult), (int)(maxDamage * mult));
    } else {
        return tcod::stringf("+%u", defence);
    }
}
