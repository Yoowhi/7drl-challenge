#include "EquipmentItem.hpp"
#include "../actions/EquipAction.hpp"
#include "libtcod.hpp"
#include "../Being.hpp"

EquipmentItem::EquipmentItem(Entity* owner, Type type, int weight) : Item(owner, weight), type(type)  {}

Action* EquipmentItem::use(Entity* user) {
    return new EquipAction(user, this);
}
