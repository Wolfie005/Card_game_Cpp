//
// Created by Sebastian Håfström on 2024-03-26.
//

#ifndef CARD_GAME_ENTITY_H
#define CARD_GAME_ENTITY_H

#include "SFML/Graphics.hpp"
#include "gameSituation.h"


using namespace sf;
using namespace std;

enum PlayerOrEnemy {
    PLAYER,
    ENEMY,
};

class Entity {
public:
    Entity(GameSituation *situation, RenderWindow *currentWindow, int health) :
            situation(situation), window(currentWindow), initialHealth((float) health), health((float) health) {

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

    void energyDisplay(int energyToken){
        energy.setOrigin(energy.getGlobalBounds().width / 2, energy.getGlobalBounds().height / 2);
        energy.setPosition(HealthBar.getPosition().x, HealthBar.getPosition().y + 50);

        energy.setString(to_string(energyToken) + " / 10");
        window->draw(energy);
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


    void doDamage(Entity *opponent) const{
        opponent->receiveDamage(damage);
    }

    void ResetGuard(){
        guard = 0;
    }

    virtual bool markedForRemoval() = 0;


protected:
    Font font;
    Text energy;
    float healthWidth;
    float damage;
    float guard;
    float initialHealth;
    float health;
    RenderWindow *window;
    RectangleShape entity;
    GameSituation *situation;
    RectangleShape HealthContainer;
    RectangleShape HealthBar;
};

#endif //CARD_GAME_ENTITY_H
