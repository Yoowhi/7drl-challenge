#pragma once
#include "../Action.hpp"
class EquipmentItem;
class Entity;

class EquipAction : public Action {
    public:
        EquipmentItem* item = nullptr;

        EquipAction(Entity* actor, EquipmentItem* item);
        void execute();
};
