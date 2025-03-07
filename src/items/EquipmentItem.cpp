#include "libtcod.hpp"
#include "../Controller.hpp"
#include "../CreatureController.hpp"
#include "../Entity.hpp"
#include "../Being.hpp"
#include "../Action.hpp"
#include "../actions/EquipAction.hpp"
#include "../actions/MoveAction.hpp"
#include "../actions/IdleAction.hpp"
#include "../actions/AttackAction.hpp"
#include "../ActionQueue.hpp"
#include "../GUI.hpp"
#include "../Engine.hpp"
#include "../Item.hpp"
#include "../Equipment.hpp"
#include "EquipmentItem.hpp"

EquipmentItem::EquipmentItem(Entity* owner, Type type) : Item(owner), type(type)  {}

Action* EquipmentItem::use(Entity* user) {
    return new EquipAction(user, this);
}
