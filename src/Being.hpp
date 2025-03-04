class Entity;

class Being {
    public:
        int hp, maxHp;
        int defence;
        Entity* owner;

        Being(Entity* owner, int maxHp, int defence);
        ~Being();

        void die();
};
