#include "EquipmentItem.hpp"
#include "../actions/EquipAction.hpp"

EquipmentItem::EquipmentItem(Entity* owner, Type type) : Item(owner), type(type)  {}

Action* EquipmentItem::use(Entity* user) {
    return new EquipAction(user, this);
}
