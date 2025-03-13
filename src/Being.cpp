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
#include "Container.hpp"
#include "items/HandsWeaponItem.hpp"
#include "items/ArmorItem.hpp"

static const int POINTS_PER_LVL = 3;
static const int HP_PER_HEALTH_POINT = 2;
static const int STAMINA_PER_ENDURANCE_POINT = 2;
static const float STAMINA_PER_TIME = 10.0f/200.0f;
static const float DEFENSE_PER_TIME = 1.0f/400.0f;

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
        Entity* entity = new Entity(0, 0, '!', Color::red, "Hands", false);
        handsWeapon = new HandsWeaponItem(entity, this);
        equipment = Equipment(owner);
        equipment.items[EquipmentItem::WEAPON] = handsWeapon;
        hp = baseHp;
        stamina = baseStamina;
    }

Being::~Being() {}

float Being::getTimeMultiplier() {
    return 1.0f - ((float)agility / 200.0f) + (getSumWeight() / 200.0f); // half of time on agility=100, x2 time when weight=100
}

float Being::getDamageMultiplier() {
    return 1.0f + (float)strength * 0.1f; // x10 damage at strength=100
}

float Being::getMaxDefense() {
    int defense = 0;
    for (auto& item : equipment.items) {
        if (item.second) {
            auto armor = dynamic_cast<ArmorItem*>(item.second);
            if (armor) {
                defense += armor->defence;
            }
        }
    }
    return (float)defense;
}

int Being::getSumWeight() {
    int weight = 0;
    for (auto& iter : equipment.items) {
        if (iter.second) {
            weight += iter.second->weight;
        }
    }
    for(auto iter : owner->inventory->items) {
        if (iter) {
            weight += iter->weight;
        }
    }
    return weight;
}

float Being::getMaxHp() {
    return baseHp + HP_PER_HEALTH_POINT * health;
}

float Being::getMaxStamina() {
    return baseStamina + STAMINA_PER_ENDURANCE_POINT * endurance;
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

void Being::updateDefense(float defense) {
    this->defense += defense;
    if (this->defense <= 0) {
        this->defense = 0;
    } else if (this->defense > getMaxDefense()) {
        this->defense = getMaxDefense();
    }
}

void Being::restoreStats(int time) {
    updateStamina((float)time * STAMINA_PER_TIME);
    updateDefense(getMaxDefense() * (float)time * DEFENSE_PER_TIME);
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



void Being::incrementStrength() {
    if (attributePoints <= 0) {
        throw "Tried to increase attribute while points=0";
    }
    strength++;
    attributePoints--;
}

void Being::incrementHealth() {
    if (attributePoints <= 0) {
        throw "Tried to increase attribute while points=0";
    }
    health++;
    attributePoints--;
    if (hp > 0) {
        hp += HP_PER_HEALTH_POINT;
    }
}

void Being::incrementAgility() {
    if (attributePoints <= 0) {
        throw "Tried to increase attribute while points=0";
    }
    agility++;
    attributePoints--;
}

void Being::incrementEndurance() {
    if (attributePoints <= 0) {
        throw "Tried to increase attribute while points=0";
    }
    endurance++;
    attributePoints--;
    if (stamina > 0) {
        stamina += STAMINA_PER_ENDURANCE_POINT;
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
