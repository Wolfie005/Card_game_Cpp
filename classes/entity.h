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
            situation(situation),window(currentWindow), health(health) {

        entity.setSize(Vector2f(50, 100));
        entity.setOrigin(entity.getSize().x / 2, entity.getSize().y / 2);
        entity.setFillColor(Color::White);
    }

    virtual void update() = 0;

    void receiveDamage(int _damage) {
        health -= _damage;
    }

    void doDamage(Entity *opponent) {
        opponent->receiveDamage(damage);
    }


protected:
    int damage;
    int health;
    RenderWindow *window;
    RectangleShape entity;
    GameSituation *situation;
};

#endif //CARD_GAME_ENTITY_H
