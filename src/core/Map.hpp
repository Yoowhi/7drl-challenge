struct Tile {
  int ch;
  TCODColor frontColor;
  TCODColor backColor;
  bool explored;

  Tile() : explored(false), backColor(TCODColor(128, 128, 128)), frontColor(TCODColor(100, 100, 100)) {};
};

class Map {
    public:
        ~Map();
        int width, height;
        int lvl;
        Tile* tiles;

    private:
        friend class MapGenerator;

        Map();

        TCODMap* walkMap;
};
