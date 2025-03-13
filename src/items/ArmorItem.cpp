#include "ArmorItem.hpp"
#include "../actions/EquipAction.hpp"
#include "libtcod.hpp"
#include "../Being.hpp"

ArmorItem::ArmorItem(Entity* owner, Type type, int weight, int defense) : EquipmentItem(owner, type, weight), defence(defense)  {}

std::string ArmorItem::getPrintStats(Being* being) {
    return tcod::stringf("%u", defence);
}
