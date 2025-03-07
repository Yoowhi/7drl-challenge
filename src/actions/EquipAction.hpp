#pragma once
#include "../Action.hpp"
#include "../items/EquipmentItem.hpp"
#include "../Entity.hpp"
class EquipmentItem;
class Entity;

class EquipAction : public Action {
    public:
        EquipmentItem* item;

        EquipAction(Entity* actor, EquipmentItem* item);
        void execute();
};
