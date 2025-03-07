#include "libtcod.hpp"
#include "CreatureFactory.hpp"
#include "CreatureController.hpp"
#include "Being.hpp"


Entity* CreatureFactory::randomCreature(int lvl, int x, int y) {
    TCODRandom* rng = TCODRandom::getInstance();
    int points = rng->getInt(0, 100);
    if (points < 50) {
        return kobold(lvl, x, y);
    } else if (points < 80) {
        return goblin(lvl, x, y);
    } else if (points < 95) {
        return orc(lvl, x, y);
    } else {
        return troll(lvl, x, y);
    }
}

Entity* CreatureFactory::kobold(int lvl, int x, int y) {
    Entity* kobold = new Entity(x, y, 'k', TCODColor::brass, "kobold", true);
    kobold->controller = new CreatureController(kobold);
    kobold->being = new Being(
        kobold,
        lvl, // lvl,
        5, // baseHp,
        10, // baseStamina,
        2, // strength,
        1, // health,
        8, // agility,
        3, // endurance,
        100
    );
    return kobold;
}

Entity* CreatureFactory::goblin(int lvl, int x, int y) {
    Entity* goblin = new Entity(x, y, 'g', TCODColor::darkGreen, "goblin", true);
    goblin->controller = new CreatureController(goblin);
    goblin->being = new Being(
        goblin,
        lvl, // lvl,
        7, // baseHp,
        10, // baseStamina,
        4, // strength,
        3, // health,
        8, // agility,
        4, // endurance
        200
    );
    return goblin;
}

Entity* CreatureFactory::orc(int lvl, int x, int y) {
    Entity* orc = new Entity(x, y, 'o', TCODColor::green, "orc", true);
    orc->controller = new CreatureController(orc);
    orc->being = new Being(
        orc,
        lvl, // lvl,
        10, // baseHp,
        20, // baseStamina,
        8, // strength,
        8, // health,
        6, // agility,
        8, // endurance
        300
    );
    return orc;
}

Entity* CreatureFactory::troll(int lvl, int x, int y) {
    Entity* troll = new Entity(x, y, 'T', TCODColor::cyan, "troll", true);
    troll->controller = new CreatureController(troll);
    troll->being = new Being(
        troll,
        lvl, // lvl,
        20, // baseHp,
        20, // baseStamina,
        15, // strength,
        15, // health,
        2, // agility,
        8, // endurance
        500
    );
    return troll;
}
