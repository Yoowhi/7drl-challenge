#include "utility.hpp"
#include "ItemFactory.hpp"
#include "items/PotionItem.hpp"
#include "items/ArmorItem.hpp"
#include "items/WeaponItem.hpp"
#include "Entity.hpp"
#include "colors.h"

Entity* ItemFactory::createItem(int lvl, int x, int y) {
    int lvlModifier = rnd(0, 3);
    return rnd(0, 1) > 0 ? createEquipmentItem(lvl + lvlModifier, x, y) : createPotionItem(lvl + lvlModifier, x, y);
}

// =====================================================================================================================

Entity* ItemFactory::createEquipmentItem(int lvl, int x, int y) {
    int type = rnd(0, 4);
    ItemFactory::Metal metal = getMetal(lvl);
    EquipmentItem::Rarity rarity = getRandomEquipmentRarity();
    switch (type) {
        case 0: return createWeaponItem(lvl, x, y, metal, rarity);
        case 1: return createHelmetItem(lvl, x, y, metal, rarity);
        case 2: return createChestItem(lvl, x, y, metal, rarity);
        case 3: return createGlovesItem(lvl, x, y, metal, rarity);
        case 4: return createBootsItem(lvl, x, y, metal, rarity);
        default: throw "Invalid choise in equipment ItemFactory";
    }
}

Entity* ItemFactory::createWeaponItem(int lvl, int x, int y, ItemFactory::Metal metal, EquipmentItem::Rarity rarity) {
    char* name;
    int symbol;
    int minDamage;
    int maxDamage;
    int weight;
    int attackSpeed;
    int weapon = rnd(0, 3);
    switch (weapon) {
        case 0:
            name = " knife";
            symbol = '-';
            minDamage = 1;
            maxDamage = 2;
            weight = 1;
            attackSpeed = 80;
            break;
        case 1:
            name = " sword";
            symbol = '|';
            minDamage = 1;
            maxDamage = 3;
            weight = 2;
            attackSpeed = 100;
            break;
        case 2:
            name = " axe";
            symbol = 'p';
            minDamage = 2;
            maxDamage = 4;
            weight = 3;
            attackSpeed = 120;
            break;
        case 3:
            name = " mace";
            symbol = '*';
            minDamage = 3;
            maxDamage = 4;
            weight = 4;
            attackSpeed = 140;
            break;
        default:
            throw "Invalid weapon in equipment ItemFactory";
    }
    Entity* entity = new Entity(x, y, symbol, metal.color, concatenate(metal.name, name), false);
    weight = weight + (float)weight * (float)lvl / 10.0f;
    minDamage = modifyStat(minDamage, lvl, rarity);
    maxDamage = modifyStat(maxDamage, lvl, rarity);
    EquipmentItem* item = new WeaponItem(entity, weight, minDamage, maxDamage, attackSpeed);
    entity->item = item;
    return entity;
}

Entity* ItemFactory::createHelmetItem(int lvl, int x, int y, ItemFactory::Metal metal, EquipmentItem::Rarity rarity) {
    Entity* entity = new Entity(x, y, 'o', metal.color, concatenate(metal.name, " helmet"), false);
    int weight = modifyStat(2, lvl, EquipmentItem::COMMON);
    int defense = modifyStat(2, lvl, rarity);
    EquipmentItem* item = new ArmorItem(entity, EquipmentItem::HELMET, weight, defense);
    entity->item = item;
    return entity;
}

Entity* ItemFactory::createChestItem(int lvl, int x, int y, ItemFactory::Metal metal, EquipmentItem::Rarity rarity) {
    Entity* entity = new Entity(x, y, '0', metal.color, concatenate(metal.name, " plate"), false);
    int weight = modifyStat(4, lvl, EquipmentItem::COMMON);
    int defense = modifyStat(4, lvl, rarity);
    EquipmentItem* item = new ArmorItem(entity, EquipmentItem::CHEST, weight, defense);
    entity->item = item;
    return entity;
}

Entity* ItemFactory::createGlovesItem(int lvl, int x, int y, ItemFactory::Metal metal, EquipmentItem::Rarity rarity) {
    Entity* entity = new Entity(x, y, '"', metal.color, concatenate(metal.name, " gloves"), false);
    int weight = modifyStat(1, lvl, EquipmentItem::COMMON);
    int defense = modifyStat(1, lvl, rarity);
    EquipmentItem* item = new ArmorItem(entity, EquipmentItem::GLOVES, weight, defense);;
    entity->item = item;
    return entity;
}

Entity* ItemFactory::createBootsItem(int lvl, int x, int y, ItemFactory::Metal metal, EquipmentItem::Rarity rarity) {
    Entity* entity = new Entity(x, y, 'b', metal.color, concatenate(metal.name, " boots"), false);
    int weight = modifyStat(1, lvl, EquipmentItem::COMMON);
    int defense = modifyStat(1, lvl, rarity);
    EquipmentItem* item = new ArmorItem(entity, EquipmentItem::BOOTS, weight, defense);
    entity->item = item;
    return entity;
}

Entity* ItemFactory::_createTestingWeapon(int lvl) {
    return createWeaponItem(lvl, 0, 0, getMetal(lvl), getRandomEquipmentRarity());
}

Entity* ItemFactory::_createTestingArmor(int lvl) {
    return createChestItem(lvl, 0, 0, getMetal(lvl), getRandomEquipmentRarity());
}

EquipmentItem::Rarity ItemFactory::getRandomEquipmentRarity() {
    int number = rnd(0, 100);
    if (number < 50) return EquipmentItem::COMMON;
    if (number < 80) return EquipmentItem::UNCOMMON;
    if (number < 90) return EquipmentItem::RARE;
    if (number < 98) return EquipmentItem::EPIC;
    if (number < 100) return EquipmentItem::LEGENDARY;
    return EquipmentItem::LEGENDARY;
}

float ItemFactory::getRarityModifier(EquipmentItem::Rarity rarity) {
    switch (rarity)
    {
        case EquipmentItem::COMMON: return 1;
        case EquipmentItem::UNCOMMON: return 1.3f;
        case EquipmentItem::RARE: return 1.6f;
        case EquipmentItem::EPIC: return 1.9f;
        case EquipmentItem::LEGENDARY: return 2.5f;
        default: throw "Unknown rarity in equipment ItemFactory";
    }
}

// =====================================================================================================================

Entity* ItemFactory::createPotionItem(int lvl, int x, int y) {
    int number = rnd(0, 9);
    if (number < 4) return createHealthPotionItem(lvl, x, y);
    if (number < 8) return createStaminaPotionItem(lvl, x, y);
    return createRestorationPotionItem(lvl, x, y);
}

Entity* ItemFactory::createHealthPotionItem(int lvl, int x, int y) {
    Entity* entity = new Entity(x, y, '`', Color::darkRed, concatenate("Red", " potion"), false);
    PotionItem* item = new PotionItem(entity);
    item->hp = 10 + lvl * 2;
    entity->item = item;
    return entity;
}

Entity* ItemFactory::createStaminaPotionItem(int lvl, int x, int y) {
    Entity* entity = new Entity(x, y, '`', Color::darkGreen, concatenate("Green", " potion"), false);
    PotionItem* item = new PotionItem(entity);
    item->stamina = 20 + lvl * 2;
    entity->item = item;
    return entity;
}

Entity* ItemFactory::createRestorationPotionItem(int lvl, int x, int y) {
    Entity* entity = new Entity(x, y, '`', Color::purple, concatenate("Purple", " potion"), false);
    PotionItem* item = new PotionItem(entity);
    item->hp = 30 + lvl * 2;
    item->stamina = 60 + lvl * 2;
    entity->item = item;
    return entity;
}

// =====================================================================================================================

ItemFactory::Metal ItemFactory::getMetal(int lvl) {
    static const Metal metalColors[numMetals] = {
        {"Bronze", tcod::ColorRGB{205, 127, 50}},
        {"Iron", tcod::ColorRGB{183, 183, 183}},
        {"Steel", tcod::ColorRGB{192, 192, 192}},
        {"Silver", tcod::ColorRGB{192, 192, 192}},
        {"Electrum", tcod::ColorRGB{255, 223, 0}},
        {"Gold", tcod::ColorRGB{255, 215, 0}},
        {"Moonsteel", tcod::ColorRGB{169, 169, 255}},
        {"Platinum", tcod::ColorRGB{229, 228, 226}},
        {"Titanium", tcod::ColorRGB{135, 206, 235}},
        {"Tungsten", tcod::ColorRGB{169, 169, 169}},
        {"Palladium", tcod::ColorRGB{209, 209, 224}},
        {"Mithril", tcod::ColorRGB{173, 216, 230}},
        {"Dragonsteel", tcod::ColorRGB{255, 69, 0}},
        {"Adamantium", tcod::ColorRGB{112, 128, 144}},
        {"Vibranium", tcod::ColorRGB{0, 255, 255}},
        {"Starmetal", tcod::ColorRGB{72, 61, 139}},
        {"Orichalcum", tcod::ColorRGB{218, 165, 32}},
        {"Frostsilver", tcod::ColorRGB{176, 224, 230}},
        {"Aetherium", tcod::ColorRGB{123, 104, 238}},
        {"Arcane", tcod::ColorRGB{138, 43, 226}}
    };

    int i = (lvl - (lvl % 2)) / 2;
    if (i >= numMetals) {
        i = numMetals - 1;
    }
    return metalColors[i];
}


float ItemFactory::modifyStat(float value, int lvl, EquipmentItem::Rarity rarity) {
    return value + value * (float)lvl / 20.0f * getRarityModifier(rarity);
}
