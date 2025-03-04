struct Tile {
  int ch;
  TCODColor frontColor;
  TCODColor backColor;
  TCODColor frontColorFaded;
  TCODColor backColorFaded;
  bool explored;

  Tile() : explored(false), backColor(TCODColor(128, 128, 128)), frontColor(TCODColor(100, 100, 100)), backColorFaded(TCODColor(64, 64, 64)), frontColorFaded(TCODColor(50, 50, 50)) {};
};

class Map {
    public:
        ~Map();
        int width, height;
        int enterX, enterY;
        int lvl;
        Tile* tiles;
        TCODList<Entity*> entities;
        TCODMap* walkMap;

        void enter(Entity* entity);
        void exit(Entity* entity);
        bool canWalk(int x, int y);
        Tile* getTile(int x, int y);

    private:
        friend class MapGenerator;

        Map();

};
