class EquipAction : public Action {
    public:
        EquipmentItem* item;

        EquipAction(Entity* actor, EquipmentItem* item);
        void execute();
};
