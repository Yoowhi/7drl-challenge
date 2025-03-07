#include <unordered_map>
#include "libtcod.hpp"
#include "Controller.hpp"
#include "CreatureController.hpp"
#include "Entity.hpp"
#include "Being.hpp"
#include "Action.hpp"
#include "actions/MoveAction.hpp"
#include "actions/IdleAction.hpp"
#include "actions/AttackAction.hpp"
#include "ActionQueue.hpp"
#include "GUI.hpp"
#include "Engine.hpp"
#include "Item.hpp"
#include "EquipmentItem.hpp"
#include "Equipment.hpp"

Equipment::Equipment(Entity* owner) : owner(owner) {}

EquipmentItem* Equipment::swapItem(EquipmentItem* item) {
    EquipmentItem* equipedItem = items[item->type];
    items[item->type] = item;
    return equipedItem;
}

EquipmentItem* Equipment::getItem(EquipmentItem::Type type) {
    return items[type];
}
