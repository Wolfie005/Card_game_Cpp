//
// Created by Sebastian Håfström on 2024-03-26.
//

#ifndef CARD_GAME_ENTITY_H
#define CARD_GAME_ENTITY_H

#include "SFML/Graphics.hpp"
#include "gameSituation.h"


using namespace sf;
using namespace std;

class Entity {
public:
    Entity(GameSituation *situation, RenderWindow *currentWindow, int health) :
            situation(situation), window(currentWindow), initialHealth((float) health), health((float) health) {

        entity.setSize(Vector2f(50, 100));
        entity.setOrigin(entity.getSize().x / 2, entity.getSize().y / 2);
        entity.setFillColor(Color::White);

    }

    virtual void update() = 0;

    void initializeHealthBar() {
        HealthBar.setSize(Vector2f(100, 25));
        HealthBar.setFillColor(Color::Green);
        HealthBar.setPosition(entity.getPosition().x, entity.getPosition().y - entity.getSize().y);
        HealthBar.setOrigin(HealthBar.getSize().x / 2, HealthBar.getSize().y / 2);


        HealthContainer.setSize(Vector2f(100, 25));
        HealthContainer.setOutlineColor(Color::Blue);
        HealthContainer.setOutlineThickness(2);
        HealthContainer.setPosition(entity.getPosition().x, entity.getPosition().y - entity.getSize().y);
        HealthContainer.setOrigin(HealthContainer.getSize().x / 2, HealthContainer.getSize().y / 2);
    }

    void updateHealthBar() {
        if (health <= 0) return;
        window->draw(HealthContainer);
        HealthBar.setSize(Vector2f((health / initialHealth) * 100, 25));
        window->draw(HealthBar);
    }

    void receiveDamage(float _damage) {
        health -= _damage;
    }

    void doDamage(Entity *opponent) const {
        opponent->receiveDamage(damage);
    }


protected:
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
