class PotionItem : public Item {
    public:
        float hp;
        float stamina;

        PotionItem(Entity* owner);

        Action* use(Entity* user);
};
