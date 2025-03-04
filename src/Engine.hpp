class Map;

class Engine {
    public:
        enum State {
            INPUT,
            TURN,
        } state;
        int screenWidth, screenHeight;
        int fovRadius;
        Map* map;
        Entity* player;
        TCOD_key_t lastKey;
        TCOD_mouse_t mouse;
        ActionQueue* actions;
        void computeFOV();

        Engine(int screenWidth, int screenHeight);
        ~Engine();

        void start();
        bool isExplored(int x, int y) const;
        bool isInFOV(int x, int y);
        Entity* getAliveEntityByCoord(int x, int y);

    protected:
        void update();
        void render();
        void renderMap();
        void renderEntities();
};

extern Engine engine;
