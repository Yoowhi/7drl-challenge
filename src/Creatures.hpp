class Entity;

class Creatures {
    public:
        static Entity* randomCreature(int lvl, int x, int y);

        static Entity* kobold(int lvl, int x, int y);
        static Entity* goblin(int lvl, int x, int y);
        static Entity* orc(int lvl, int x, int y);
        static Entity* troll(int lvl, int x, int y);
};
