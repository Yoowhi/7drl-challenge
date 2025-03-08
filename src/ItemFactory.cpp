#include "utility.hpp"
#include "ItemFactory.hpp"
#include "items/PotionItem.hpp"
#include "Entity.hpp"

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
        default: throw std::runtime_error("Invalid choise in equipment ItemFactory");
    }
}

Entity* ItemFactory::createWeaponItem(int lvl, int x, int y, ItemFactory::Metal metal, EquipmentItem::Rarity rarity) {
    char* name;
    int symbol;
    int minDamage;
    int maxDamage;
    int weight;
    int weapon = rnd(0, 3);
    switch (weapon) {
        case 0:
            name = " knife";
            symbol = '-';
            minDamage = 1;
            maxDamage = 2;
            weight = 1;
            break;
        case 1:
            name = " sword";
            symbol = '|';
            minDamage = 1;
            maxDamage = 3;
            weight = 2;
            break;
        case 2:
            name = " axe";
            symbol = 'p';
            minDamage = 2;
            maxDamage = 4;
            weight = 3;
            break;
        case 3:
            name = " mace";
            symbol = '*';
            minDamage = 4;
            maxDamage = 5;
            weight = 4;
            break;
        default:
            throw std::runtime_error("Invalid weapon in equipment ItemFactory");
    }
    Entity* entity = new Entity(x, y, symbol, metal.color, concatenate(metal.name, name), false);
    EquipmentItem* item = new EquipmentItem(entity, EquipmentItem::WEAPON);
    item->minDamage = minDamage + minDamage * (lvl + getRarityLvlModifier(rarity)) / 2;
    item->maxDamage = maxDamage + maxDamage * (lvl + getRarityLvlModifier(rarity)) / 2;
    int weightLvlModifier = lvl - getRarityLvlModifier(rarity);
    if (weightLvlModifier <= 0) weightLvlModifier = 1;
    item->weight = 1 + weight * (lvl - getRarityLvlModifier(rarity)) / 2;
    entity->item = item;
    return entity;
}

Entity* ItemFactory::createHelmetItem(int lvl, int x, int y, ItemFactory::Metal metal, EquipmentItem::Rarity rarity) {
    Entity* entity = new Entity(x, y, 'o', metal.color, concatenate(metal.name, " helmet"), false);
    EquipmentItem* item = new EquipmentItem(entity, EquipmentItem::HELMET);
    item->defence = 4 * (lvl + getRarityLvlModifier(rarity)) / 2;
    int weightLvlModifier = lvl - getRarityLvlModifier(rarity);
    if (weightLvlModifier <= 0) weightLvlModifier = 1;
    item->weight = 2 + 2 * (lvl - getRarityLvlModifier(rarity)) / 2;
    entity->item = item;
    return entity;
}

Entity* ItemFactory::createChestItem(int lvl, int x, int y, ItemFactory::Metal metal, EquipmentItem::Rarity rarity) {
    Entity* entity = new Entity(x, y, '0', metal.color, concatenate(metal.name, " plate"), false);
    EquipmentItem* item = new EquipmentItem(entity, EquipmentItem::CHEST);
    item->defence = 4 * (lvl + getRarityLvlModifier(rarity)) / 2;
    int weightLvlModifier = lvl - getRarityLvlModifier(rarity);
    if (weightLvlModifier <= 0) weightLvlModifier = 1;
    item->weight = 4 + 4 * (lvl - getRarityLvlModifier(rarity)) / 2;
    entity->item = item;
    return entity;
}

Entity* ItemFactory::createGlovesItem(int lvl, int x, int y, ItemFactory::Metal metal, EquipmentItem::Rarity rarity) {
    Entity* entity = new Entity(x, y, '"', metal.color, concatenate(metal.name, " gloves"), false);
    EquipmentItem* item = new EquipmentItem(entity, EquipmentItem::GLOVES);
    item->defence = 1 * (lvl + getRarityLvlModifier(rarity)) / 2;
    int weightLvlModifier = lvl - getRarityLvlModifier(rarity);
    if (weightLvlModifier <= 0) weightLvlModifier = 1;
    item->weight = 1 + 1 * (lvl - getRarityLvlModifier(rarity)) / 2;
    entity->item = item;
    return entity;
}

Entity* ItemFactory::createBootsItem(int lvl, int x, int y, ItemFactory::Metal metal, EquipmentItem::Rarity rarity) {
    Entity* entity = new Entity(x, y, 'b', metal.color, concatenate(metal.name, " boots"), false);
    EquipmentItem* item = new EquipmentItem(entity, EquipmentItem::BOOTS);
    item->defence = 2 * (lvl + getRarityLvlModifier(rarity)) / 2;
    int weightLvlModifier = lvl - getRarityLvlModifier(rarity);
    if (weightLvlModifier <= 0) weightLvlModifier = 1;
    item->weight = 1 + 1 * (lvl - getRarityLvlModifier(rarity)) / 2;
    entity->item = item;
    return entity;
}

Entity* ItemFactory::_createTestingWeapon(int lvl, int x, int y) {
    return createWeaponItem(lvl, x, y, getMetal(lvl), getRandomEquipmentRarity());
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

int ItemFactory::getRarityLvlModifier(EquipmentItem::Rarity rarity) {
    switch (rarity)
    {
        case EquipmentItem::COMMON: return 0;
        case EquipmentItem::UNCOMMON: return 2;
        case EquipmentItem::RARE: return 4;
        case EquipmentItem::EPIC: return 6;
        case EquipmentItem::LEGENDARY: return 8;
        default: throw std::runtime_error("Unknown rarity in equipment ItemFactory");
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
    Entity* entity = new Entity(x, y, '`', TCODColor::darkRed, concatenate("Red", " potion"), false);
    PotionItem* item = new PotionItem(entity);
    item->hp = 10 + lvl * 2;
    entity->item = item;
    return entity;
}

Entity* ItemFactory::createStaminaPotionItem(int lvl, int x, int y) {
    Entity* entity = new Entity(x, y, '`', TCODColor::darkGreen, concatenate("Green", " potion"), false);
    PotionItem* item = new PotionItem(entity);
    item->stamina = 20 + lvl * 2;
    entity->item = item;
    return entity;
}

Entity* ItemFactory::createRestorationPotionItem(int lvl, int x, int y) {
    Entity* entity = new Entity(x, y, '`', TCODColor::purple, concatenate("Purple", " potion"), false);
    PotionItem* item = new PotionItem(entity);
    item->hp = 30 + lvl * 2;
    item->stamina = 60 + lvl * 2;
    entity->item = item;
    return entity;
}

// =====================================================================================================================

ItemFactory::Metal ItemFactory::getMetal(int lvl) {
    static const Metal metalColors[numMetals] = {
        {"Bronze", TCODColor(205, 127, 50)},
        {"Iron", TCODColor(183, 183, 183)},
        {"Steel", TCODColor(192, 192, 192)},
        {"Silver", TCODColor(192, 192, 192)},
        {"Electrum", TCODColor(255, 223, 0)},
        {"Gold", TCODColor(255, 215, 0)},
        {"Moonsteel", TCODColor(169, 169, 255)},
        {"Platinum", TCODColor(229, 228, 226)},
        {"Titanium", TCODColor(135, 206, 235)},
        {"Tungsten", TCODColor(169, 169, 169)},
        {"Palladium", TCODColor(209, 209, 224)},
        {"Mithril", TCODColor(173, 216, 230)},
        {"Dragonsteel", TCODColor(255, 69, 0)},
        {"Adamantium", TCODColor(112, 128, 144)},
        {"Vibranium", TCODColor(0, 255, 255)},
        {"Starmetal", TCODColor(72, 61, 139)},
        {"Orichalcum", TCODColor(218, 165, 32)},
        {"Frostsilver", TCODColor(176, 224, 230)},
        {"Aetherium", TCODColor(123, 104, 238)},
        {"Arcane", TCODColor(138, 43, 226)}
    };

    int i = (lvl - (lvl % 2)) / 2;
    if (i >= numMetals) {
        i = numMetals - 1;
    }
    return metalColors[i];
}
