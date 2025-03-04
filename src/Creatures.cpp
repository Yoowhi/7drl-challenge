#include "libtcod.hpp"
#include "Controller.hpp"
#include "CreatureController.hpp"
#include "Entity.hpp"
#include "Creatures.hpp"

Entity* Creatures::randomCreature(int lvl, int x, int y) {
    TCODRandom* rng = TCODRandom::getInstance();
    int points = rng->getInt(0, 100);
    if (points < 50) {
        return kobold(x, y);
    } else if (points < 80) {
        return goblin(x, y);
    } else if (points < 95) {
        return orc(x, y);
    } else {
        return troll(x, y);
    }
}

Entity* Creatures::kobold(int x, int y) {
    Entity* kobold = new Entity(x, y, 'k', TCODColor::brass, "kobold", true);
    kobold->controller = new CreatureController(kobold);
    return kobold;
}

Entity* Creatures::goblin(int x, int y) {
    Entity* goblin = new Entity(x, y, 'g', TCODColor::darkGreen, "goblin", true);
    goblin->controller = new CreatureController(goblin);
    return goblin;
}

Entity* Creatures::orc(int x, int y) {
    Entity* orc = new Entity(x, y, 'o', TCODColor::green, "orc", true);
    orc->controller = new CreatureController(orc);
    return orc;
}

Entity* Creatures::troll(int x, int y) {
    Entity* troll = new Entity(x, y, 'T', TCODColor::cyan, "troll", true);
    troll->controller = new CreatureController(troll);
    return troll;
}
