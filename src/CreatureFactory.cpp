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
        15, // baseHp,
        10, // baseStamina,
        0, // strength,
        0, // health,
        0, // agility,
        0, // endurance
        1
    );
    player->being->attributePoints = 10;
    player->inventory = new Container(player);
    Entity* weapon = ItemFactory::_createTestingWeapon(1);
    Entity* armor = ItemFactory::_createTestingArmor(1);
    player->inventory->putIn(weapon->item);
    player->inventory->putIn(armor->item);
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
    kobold->inventory = new Container(kobold);
    kobold->being = new Being(
        kobold,
        lvl, // lvl,
        5, // baseHp,
        10, // baseStamina,
        1, // strength,
        1, // health,
        7, // agility,
        1, // endurance,
        100
    );
    return kobold;
}

Entity* CreatureFactory::goblin(int lvl, int x, int y) {
    Entity* goblin = new Entity(x, y, 'g', Color::darkGreen, "goblin", true);
    goblin->controller = new CreatureController(goblin);
    goblin->inventory = new Container(goblin);
    goblin->being = new Being(
        goblin,
        lvl, // lvl,
        7, // baseHp,
        10, // baseStamina,
        3, // strength,
        1, // health,
        5, // agility,
        1, // endurance
        200
    );
    return goblin;
}

Entity* CreatureFactory::orc(int lvl, int x, int y) {
    Entity* orc = new Entity(x, y, 'o', Color::green, "orc", true);
    orc->controller = new CreatureController(orc);
    orc->inventory = new Container(orc);
    orc->being = new Being(
        orc,
        lvl, // lvl,
        10, // baseHp,
        20, // baseStamina,
        5, // strength,
        2, // health,
        1, // agility,
        2, // endurance
        300
    );
    return orc;
}

Entity* CreatureFactory::troll(int lvl, int x, int y) {
    Entity* troll = new Entity(x, y, 'T', Color::cyan, "troll", true);
    troll->controller = new CreatureController(troll);
    troll->inventory = new Container(troll);
    troll->being = new Being(
        troll,
        lvl, // lvl,
        20, // baseHp,
        20, // baseStamina,
        6, // strength,
        4, // health,
        0, // agility,
        0, // endurance
        500
    );
    return troll;
}
