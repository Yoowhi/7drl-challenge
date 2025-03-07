class DrinkPotionAction : public Action {
    public:
        PotionItem* item;

        DrinkPotionAction(Entity* actor, PotionItem* item);
        void execute();
};
