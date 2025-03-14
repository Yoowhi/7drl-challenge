#pragma once
class Entity;
class Item;

class Container {
    public:
        Entity* owner = nullptr;
        static const int CONTAINER_SIZE = 5;
        Item* items[CONTAINER_SIZE] = {nullptr};

        Container(Entity* owner);
        ~Container();
        bool putIn(Item* item);
        void remove(Item* item);
        Item* getItem(int id);

    private:
        Item* getOut(int id);

};
