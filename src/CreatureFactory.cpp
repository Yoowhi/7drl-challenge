#include "libtcod.hpp"
#include "CreatureController.hpp"
#include "PlayerController.hpp"
#include "Being.hpp"
#include "Container.hpp"
#include "Entity.hpp"
#include "CreatureFactory.hpp"
#include "ItemFactory.hpp"
#include "colors.h"

Entity* CreatureFactory::newPlayer() {
    Entity* player = new Entity(0, 0, '@', Color::white, "Hero", true);
    player->controller = new PlayerController(player);
    player->being = new Being(
        player,
        1, // lvl,
        50, // baseHp,
        50, // baseStamina,
        10, // strength,
        10, // health,
        10, // agility,
        10, // endurance
        1
    );
    player->inventory = new Container(player);
    Entity* weapon = ItemFactory::_createTestingWeapon(20, 0, 0);
    player->inventory->putIn(weapon->item);
    player->being->updateHp(player->being->getMaxHp());
    player->being->updateStamina(player->being->getMaxStamina());
    return player;
}


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
    Entity* kobold = new Entity(x, y, 'k', Color::brass, "kobold", true);
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
    Entity* goblin = new Entity(x, y, 'g', Color::darkGreen, "goblin", true);
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
    Entity* orc = new Entity(x, y, 'o', Color::green, "orc", true);
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
    Entity* troll = new Entity(x, y, 'T', Color::cyan, "troll", true);
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
