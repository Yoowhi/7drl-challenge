class Being;

class Entity {
    public:
        int x, y;
        int symbol;
        TCODColor color;
        char* name;
        bool blocks;

        // components
        Controller* controller;
        Being* being;

        Entity(int x, int y, int symbol, TCODColor color, char* name, bool blocks);
        ~Entity();
        void update();
        bool isAlive();
};
