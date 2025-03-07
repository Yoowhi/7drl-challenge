#include "libtcod.hpp"
#include "../Controller.hpp"
#include "../CreatureController.hpp"
#include "../Entity.hpp"
#include "../Being.hpp"
#include "../Action.hpp"
#include "../actions/DrinkPotionAction.hpp"
#include "../ActionQueue.hpp"
#include "../GUI.hpp"
#include "../Engine.hpp"
#include "../Item.hpp"
#include "../Equipment.hpp"
#include "PotionItem.hpp"

PotionItem::PotionItem(Entity* owner) : Item(owner) {}

Action* PotionItem::use(Entity* user) {
    return new DrinkPotionAction(user, this);
}
