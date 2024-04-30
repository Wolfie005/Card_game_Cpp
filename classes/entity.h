//
// Created by Sebastian Håfström on 2024-03-26.
//

#ifndef CARD_GAME_ENTITY_H
#define CARD_GAME_ENTITY_H

#include "SFML/Graphics.hpp"
#include "gameSituation.h"
#include "Item.h"


using namespace sf;
using namespace std;

enum PlayerOrEnemy {
    PLAYER,
    ENEMY,
};

class Entity {
public:
    Entity(GameSituation *situation, RenderWindow *currentWindow, int health) :
            situation(situation), window(currentWindow), initialHealth((float) health), health((float) health),
            Shield(*new Item(situation, WeaponType::BASE, &GameWave)),
            Weapon(*new Item(situation, WeaponType::BASE, &GameWave)) {

        entity.setSize(Vector2f(50, 100));
        entity.setOrigin(entity.getSize().x / 2, entity.getSize().y / 2);
        entity.setFillColor(Color::White);

        if (!font.loadFromFile("../fonts/Roboto-Light.ttf")) {
            cout << "Error loading font";
            exit(1);
        }
        energy.setFont(font);
    }


    virtual void update() = 0;

    void initializeHealthBar(PlayerOrEnemy playerOrEnemy) {

        HealthBar.setFillColor(Color::Green);


        HealthContainer.setOutlineColor(Color::Blue);
        HealthContainer.setOutlineThickness(2);

        if (playerOrEnemy == PlayerOrEnemy::ENEMY) {
            healthWidth = 100;
            HealthBar.setSize(Vector2f(healthWidth, 25));
            HealthBar.setPosition(entity.getPosition().x, entity.getPosition().y - entity.getSize().y);
            HealthContainer.setSize(Vector2f(healthWidth, 25));
            HealthContainer.setPosition(entity.getPosition().x, entity.getPosition().y - entity.getSize().y);

        } else {
            healthWidth = 250;
            HealthBar.setSize(Vector2f(healthWidth, 25));
            HealthBar.setPosition(entity.getPosition().x - (float) window->getSize().x / 3,
                                  (float) entity.getPosition().y - entity.getSize().y * 1.5f);
            HealthContainer.setSize(Vector2f(healthWidth, 25));
            HealthContainer.setPosition(entity.getPosition().x - (float) window->getSize().x / 3,
                                        (float) entity.getPosition().y - entity.getSize().y * 1.5f);
        }
        HealthContainer.setOrigin(HealthContainer.getSize().x / 2, HealthContainer.getSize().y / 2);
        HealthBar.setOrigin(HealthBar.getSize().x / 2, HealthBar.getSize().y / 2);
    }

    void updateHealthBar() {
        if (health <= 0) return;
        window->draw(HealthContainer);
        HealthBar.setSize(Vector2f((health / initialHealth) * healthWidth, 25));
        window->draw(HealthBar);
    }


    void energyDisplay(int energyToken) {
        energy.setOrigin(energy.getGlobalBounds().width / 2, energy.getGlobalBounds().height / 2);
        energy.setPosition(HealthBar.getPosition().x, HealthBar.getPosition().y + 50);

        energy.setString(to_string(energyToken) + " / 10");
        window->draw(energy);
    }

    void characterDisplay(const string &CharacterFilePath, const string &SwordFilePath, const string &ShieldFilePath) {
        CharacterImg.loadFromFile(CharacterFilePath);
        Character.setTexture(CharacterImg);
        Character.setOrigin(Character.getGlobalBounds().width / 2, Character.getGlobalBounds().height / 2);
        Character.setPosition(HealthBar.getPosition().x - 200, HealthBar.getPosition().y);
        Character.setScale(0.5f, 0.5f);

        CharacterContainer.setSize(
                Vector2f(Character.getGlobalBounds().width + 2, Character.getGlobalBounds().height + 2));
        CharacterContainer.setOrigin(CharacterContainer.getSize().x / 2, CharacterContainer.getSize().y / 2);
        CharacterContainer.setPosition(Character.getPosition().x, Character.getPosition().y);
        CharacterContainer.setOutlineColor(Color::Blue);
        CharacterContainer.setOutlineThickness(2);
        CharacterContainer.setFillColor(Color::Transparent);

        SwordImg.loadFromFile(SwordFilePath);
        Sword.setTexture(SwordImg);
        Sword.setOrigin(Sword.getGlobalBounds().width / 2, Sword.getGlobalBounds().height / 2);
        Sword.setPosition(Character.getPosition().x + 50, Character.getPosition().y + 50);
        Sword.setScale(0.2f, 0.2f);

        SwordContainer.setSize(Vector2f(Sword.getGlobalBounds().width - 2, Sword.getGlobalBounds().height - 2));
        SwordContainer.setOrigin(SwordContainer.getSize().x / 2, SwordContainer.getSize().y / 2);
        SwordContainer.setPosition(Sword.getPosition().x, Sword.getPosition().y);
        SwordContainer.setOutlineColor(Color::Blue);
        SwordContainer.setOutlineThickness(2);
        SwordContainer.setFillColor(Color::Transparent);

        ShieldImg.loadFromFile(ShieldFilePath);
        ShieldSprite.setTexture(ShieldImg);
        ShieldSprite.setOrigin(ShieldSprite.getGlobalBounds().width / 2, ShieldSprite.getGlobalBounds().height / 2);
        ShieldSprite.setPosition(Character.getPosition().x - 50, Character.getPosition().y + 50);
        ShieldSprite.setScale(0.23f, 0.18f);

        ShieldContainer.setSize(
                Vector2f(ShieldSprite.getGlobalBounds().width - 2, ShieldSprite.getGlobalBounds().height - 2));
        ShieldContainer.setOrigin(ShieldContainer.getSize().x / 2, ShieldContainer.getSize().y / 2);
        ShieldContainer.setPosition(ShieldSprite.getPosition().x, ShieldSprite.getPosition().y);
        ShieldContainer.setOutlineColor(Color::Blue);
        ShieldContainer.setOutlineThickness(2);
        ShieldContainer.setFillColor(Color::Transparent);

        DamageDisplay.setString(to_string((int) Weapon.getDamage()));
        DamageDisplay.setFont(font);
        DamageDisplay.setOrigin((DamageDisplay.getGlobalBounds().width / 2) + 3,
                                (DamageDisplay.getGlobalBounds().height / 2) + 7);
        DamageDisplay.setPosition(Sword.getPosition().x, Sword.getPosition().y + 50);

        GuardDisplay.setString(to_string((int) Shield.getGuard()));
        GuardDisplay.setFont(font);
        GuardDisplay.setOrigin((GuardDisplay.getGlobalBounds().width / 2) + 3,
                               (GuardDisplay.getGlobalBounds().height / 2) + 7);
        GuardDisplay.setPosition(ShieldSprite.getPosition().x, ShieldSprite.getPosition().y + 50);


    }

    void updateCharacterDisplay() {
        DamageDisplay.setString(to_string((int)Weapon.getDamage()));
        DamageDisplay.setOrigin((DamageDisplay.getGlobalBounds().width / 2) + 3,
                                (DamageDisplay.getGlobalBounds().height / 2) + 7);
        GuardDisplay.setString(to_string((int)Shield.getGuard()));
        GuardDisplay.setOrigin((GuardDisplay.getGlobalBounds().width / 2) + 3,
                               (GuardDisplay.getGlobalBounds().height / 2) + 7);
        window->draw(Character);
        window->draw(CharacterContainer);

        window->draw(Sword);
        window->draw(SwordContainer);
        window->draw(DamageDisplay);

        window->draw(ShieldSprite);
        window->draw(ShieldContainer);
        window->draw(GuardDisplay);

    }

    void receiveDamage(float _damage) {
        float toDeal = _damage;
        if (guard > 0) {
            toDeal = abs(guard -= _damage);
        }
        if (toDeal > 0 && guard <= 0) {
            health -= toDeal;
        }

    }



    void doDamage(Entity *opponent) const {
        opponent->receiveDamage((float) Weapon.getDamage());
    }

    float getGuard() const {
        return guard;
    }

    float getHealth() const {
        return health;
    }

    float getInitialHealth() const {
        return initialHealth;
    }

    void setHealth(float health) {
        Entity::health = health;
    }

    void resetHealth(){
        health = initialHealth;
    }

    void setGuard(float guard) {
        Entity::guard = guard;
    }

    void ResetGuard() {
        guard = 0;
    }

    virtual bool markedForRemoval() = 0;

    void setIsSelected(bool isSelected) {
        if (isSelected) {
            entity.setOutlineColor(Color::Red);
            entity.setOutlineThickness(2);
            _isSelected = true;
        } else {
            entity.setOutlineThickness(0);
            _isSelected = false;
        }
    }



    Item *getWeapon() {
        return &Weapon;
    }

    void setWeapon(const Item &weapon) {
        Weapon = weapon;

    }

    Item *getShield() {
        return &Shield;
    }

    void setShield(const Item &shield) {
        Shield = shield;
    }

    Item *getTempItem() const {
        return TempItem;
    }

    WeaponType getTempItemType() const {
        return TempItem->getWeaponType();
    };

    void setTempItem(Item *tempItem) {
        TempItem = tempItem;
    }

protected:
    Texture CharacterImg;
    Sprite Character;

    RectangleShape CharacterContainer;
    Texture SwordImg;
    Sprite Sword;
    RectangleShape SwordContainer;
    Texture ShieldImg;
    Sprite ShieldSprite;
    RectangleShape ShieldContainer;
    Text DamageDisplay;
    Text GuardDisplay;


    Font font;
    Text energy;

    float healthWidth;
    float guard = 0;
    float initialHealth;
    float health;

    Item Weapon;
    Item Shield;
    Item *TempItem;


    RenderWindow *window;
    RectangleShape entity;
    GameSituation *situation;
    RectangleShape HealthContainer;
    RectangleShape HealthBar;

    bool _isSelected = false;
};

#endif //CARD_GAME_ENTITY_H
