class Map;

class Engine {
    public:
        int screenWidth, screenHeight;
        Map* map;
        TCOD_key_t lastKey;
        TCOD_mouse_t mouse;

        Engine(int screenWidth, int screenHeight);
        ~Engine();

        void start();

    protected:
        void update();
        void render();
        void renderMap();
};

extern Engine engine;
