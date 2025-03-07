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


Item::Item(Entity* owner) : owner(owner), wearer(NULL) {}
