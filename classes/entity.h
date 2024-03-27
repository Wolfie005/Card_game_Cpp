//
// Created by Sebastian Håfström on 2024-03-26.
//

#ifndef CARD_GAME_ENTITY_H
#define CARD_GAME_ENTITY_H

#include "SFML/Graphics.hpp"
#include "gameSituation.h"


using namespace sf;
using namespace std;

enum PlayerOrNot {
    PLAYER,
    NOT,
};

class Entity {
public:
    Entity(GameSituation *situation, RenderWindow *currentWindow, int health) :
            situation(situation), window(currentWindow), initialHealth((float) health), health((float) health) {

        entity.setSize(Vector2f(50, 100));
        entity.setOrigin(entity.getSize().x / 2, entity.getSize().y / 2);
        entity.setFillColor(Color::White);
    }

    virtual void update() = 0;

    void initializeHealthBar(PlayerOrNot playerOrNot) {

        HealthBar.setFillColor(Color::Green);


        HealthContainer.setOutlineColor(Color::Blue);
        HealthContainer.setOutlineThickness(2);

        if (playerOrNot == PlayerOrNot::NOT) {
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

    void receiveDamage(float _damage) {
        health -= _damage;
    }

    void doDamage(Entity *opponent) const {
        opponent->receiveDamage(damage);
    }


protected:
    float healthWidth;
    float damage;
    float initialHealth;
    float health;
    RenderWindow *window;
    RectangleShape entity;
    GameSituation *situation;
    RectangleShape HealthContainer;
    RectangleShape HealthBar;
};

#endif //CARD_GAME_ENTITY_H
