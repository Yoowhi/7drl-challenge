#pragma once
#include "libtcod.hpp"
#include "items/EquipmentItem.hpp"
#include "colors.h"
class Entity;

class ItemFactory {
    public:
        struct Metal {
            const char* name = nullptr;
            tcod::ColorRGB color;
        };
        static const int numMetals = 20;

        static Entity* createItem(int lvl, int x, int y);

        static Entity* createEquipmentItem(int lvl, int x, int y);
        static Entity* createWeaponItem(int lvl, int x, int y, ItemFactory::Metal metal, EquipmentItem::Rarity rarity);
        static Entity* createHelmetItem(int lvl, int x, int y, ItemFactory::Metal metal, EquipmentItem::Rarity rarity);
        static Entity* createChestItem(int lvl, int x, int y, ItemFactory::Metal metal, EquipmentItem::Rarity rarity);
        static Entity* createGlovesItem(int lvl, int x, int y, ItemFactory::Metal metal, EquipmentItem::Rarity rarity);
        static Entity* createBootsItem(int lvl, int x, int y, ItemFactory::Metal metal, EquipmentItem::Rarity rarity);
        static Entity* _createTestingWeapon(int lvl);
        static Entity* _createTestingArmor(int lvl);

        static Entity* createPotionItem(int lvl, int x, int y);
        static Entity* createHealthPotionItem(int lvl, int x, int y);
        static Entity* createStaminaPotionItem(int lvl, int x, int y);
        static Entity* createRestorationPotionItem(int lvl, int x, int y);

    private:
        static EquipmentItem::Rarity getRandomEquipmentRarity();
        static float getRarityModifier(EquipmentItem::Rarity rarity);
        static float modifyStat(float value, int lvl, EquipmentItem::Rarity rarity);
        static Metal getMetal(int level);

};
