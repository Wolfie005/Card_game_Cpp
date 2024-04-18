//
// Created by Sebastian Håfström on 2024-04-15.
//
#include "SFML/Graphics.hpp"
#include "randomEngine.h"
#include "KeyHandler.h"
#include "gameSituation.h"

#ifndef CARD_GAME_ITEM_H
#define CARD_GAME_ITEM_H

using namespace std;
using namespace sf;

enum WeaponType {
    SWORD,
    SHIELD,
    BASE
};


class Item {
public:
    Item(GameSituation *situation, WeaponType weaponType, int *GameWave) : situation(situation),
                                                                           weaponType(weaponType) {
        WeaponRarityDistribution = uniform_int_distribution(0, 900000);
        RarityDeclare();
        WeaponDamageDistribution = uniform_real_distribution<float>(10 * Rarity * (float) *GameWave,
                                                                    100 * Rarity * (float) *GameWave);

        switch (weaponType) {
            case SWORD:
                damage = floorf(WeaponDamageDistribution(*engine) * 100) / 100;
                break;
            case SHIELD:
                guard = floorf(WeaponDamageDistribution(*engine) * 100) / 100;
                break;
            default:
                damage = 5;
                guard = 10;
                break;

        }

    };

    WeaponType getWeaponType() const {
        return weaponType;
    }

    [[nodiscard]] float getDamage() const {
        return damage;
    }

    void setDamage(float newDamage) {
        damage = newDamage;
    }

    [[nodiscard]] float getGuard() const {
        return guard;
    }

    void setGuard(float newGuard) {
        guard = newGuard;
    }


    void RarityDeclare() {
        int RarityType = WeaponRarityDistribution(*engine);
        if ((700000 <= RarityType && RarityType <= 950000) && GameWave >= 20) {
            Rarity = 2.0f;
        } else {
            Rarity = 0.2f;
        }
        if ((950001 <= RarityType && RarityType <= 1000000) && GameWave >= 50) {
            Rarity = 20.0f;
        } else {
            Rarity = 0.2f;
        }
    }

private:
    float Rarity = 0;
    float damage = 0;
    float guard = 0;
    Font font;
    Text Answer;
    WeaponType weaponType;
    GameSituation *situation;

    mt19937 *engine = RandomEngine::getInstance().getEngine();
    uniform_int_distribution<> WeaponRarityDistribution;
    uniform_real_distribution<float> WeaponDamageDistribution;
};

#endif //CARD_GAME_ITEM_H
