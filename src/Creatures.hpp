class Entity;

class Creatures {
    public:
        static Entity* randomCreature(int lvl, int x, int y);

        static Entity* kobold(int x, int y);
        static Entity* goblin(int x, int y);
        static Entity* orc(int x, int y);
        static Entity* troll(int x, int y);
};
