class Entity {
    public:
        int x, y;
        int symbol;
        TCODColor color;
        const char* name;
        bool blocks;
        Controller* controller;

        Entity(int x, int y, int symbol, TCODColor color, const char* name, bool blocks);
        ~Entity();
        void update();
};
