class PickUpItemAction : public Action {
    public:
        Item* item;

        PickUpItemAction(Entity* actor, Item* item);
        void execute();
};
