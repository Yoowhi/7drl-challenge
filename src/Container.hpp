class Container {
    public:
        Entity* owner;
        Item* items[10];

        Container(Entity* owner);
        bool putIn(Item* item);
        Item* getOut(int id);
        void remove(Item* item);

    private:
        static const int CONTAINER_SIZE = 10;
};
