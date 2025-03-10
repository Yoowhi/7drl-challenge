#include "libtcod.hpp"
#include "utility.hpp"
#include "Being.hpp"
#include "Engine.hpp"
#include "Map.hpp"
#include "Entity.hpp"
#include "GUI.hpp"
#include "ActionQueue.hpp"
#include "math.h"
#include "colors.h"

static const int POINTS_PER_LVL = 3;
static const int HP_PER_HEALTH_POINT = 2;
static const int STAMINA_PER_ENDURANCE_POINT = 2;
static const int STAMINA_TIME_DIVIDER = 100;

Being::Being(
    Entity* owner,
    int lvl,
    float baseHp,
    float baseStamina,
    int strength,
    int health,
    int agility,
    int endurance,
    int xpForKill
) : owner(owner),
    lvl(lvl),
    xp(0),
    baseHp(baseHp),
    baseStamina(baseStamina),
    strength(strength),
    health(health),
    agility(agility),
    endurance(endurance),
    xpForKill(xpForKill),
    equipment(owner) {
        equipment = Equipment(owner);
        hp = baseHp;
        stamina = baseStamina;
    }

Being::~Being() {}

float Being::getTimeMultiplier() {
    return 1.0f - (float)agility * 0.005f; // half of time on agility=100
}

float Being::getDamageMultiplier() {
    return 1.0f + (float)strength * 0.2f; // x20 damage at strength=100
}

int Being::getDefense() {
    int defense = 0;
    for (auto& item : equipment.items) {
        if (item.second) {
            defense += item.second->defence;
        }
    }
    return defense;
}

float Being::getMinHandDamage() {
    return 1.0f;
}

float Being::getMaxHandDamage() {
    return 2.0f;
}

float Being::getMaxHp() {
    return baseHp + HP_PER_HEALTH_POINT * health;
}

float Being::getMaxStamina() {
    return baseStamina + HP_PER_HEALTH_POINT * health;
}

void Being::updateHp(float hp) {
    this->hp += hp;
    if (this->hp <= 0) {
        this->hp = 0;
        die();
    } else if (this->hp > getMaxHp()) {
        this->hp = getMaxHp();
    }
}

void Being::updateStamina(float stamina) {
    this->stamina += stamina;
    if (this->stamina <= 0) {
        this->stamina = 0;
    } else if (this->stamina > getMaxStamina()) {
        this->stamina = getMaxStamina();
    }
}

void Being::restoreStamina(int time) {
    updateStamina(0.05f * getMaxStamina() * ((float)time / STAMINA_TIME_DIVIDER));
}

void Being::addXp(int amount) {
    xp += amount;
    int currentLvlCap = getMaxXp();
    if (xp >= currentLvlCap) {
        xp = xp - currentLvlCap;
        lvl++;
        attributePoints += POINTS_PER_LVL;
    }
}

int Being::getMaxXp() {
    return 500 * (int)powf(2, lvl);
}

void Being::autoIncreaseAttributes(int lvlUps, int priorityStrength, int priorityHealth, int priorityAgility, int priorityEndurance) {
    int points = lvlUps * POINTS_PER_LVL;
    int sum = priorityStrength + priorityHealth + priorityAgility + priorityEndurance;
    priorityHealth = priorityStrength + priorityHealth;
    priorityAgility = priorityStrength + priorityHealth + priorityAgility;
    for (int i = 0; i < points; i++) {
        int number = rnd(0, sum);
        if (number < priorityStrength) {
            strength++;
        } else if (number < priorityHealth) {
            incrementHealth();
        } else if (number < priorityAgility) {
            agility++;
        } else {
            incrementEndurance();
        }
    }
}

void Being::incrementEndurance() {
    endurance++;
    if (stamina > 0) {
        stamina += STAMINA_PER_ENDURANCE_POINT;
    }
}
void Being::incrementHealth() {
    health++;
    if (hp > 0) {
        hp += HP_PER_HEALTH_POINT;
    }
}

void Being::die() {
    owner->blocks = false;
    owner->color = Color::darkestGrey;
    Tile* tile = engine->map->getTile(owner->x, owner->y);
    tile->backColor = Color::darkerRed;
    tile->backColorFaded = Color::darkestRed;
    engine->gui->message(Color::white, tcod::stringf("%s died", owner->name));
    char* newName = concatenate("dead ", owner->name);
    delete[] owner->name;
    owner->name = newName;
    engine->actions->clearFromActor(owner);
}

int Being::getXpForKill() {
    return xpForKill * lvl;
}
