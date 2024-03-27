//
// Created by Sebastian Håfström on 2024-03-26.
//

#ifndef CARD_GAME_PLAYER_H
#define CARD_GAME_PLAYER_H

#include "SFML/Graphics.hpp"
#include "entity.h"
#include "KeyHandler.h"

using namespace sf;
using namespace std;

class Player : public Entity {
public:
    Player(GameSituation *situation, RenderWindow *currentWindow, Keyboard::Key attackKey, Keyboard::Key RightSelectKey,
           vector<Entity *> *enemies)
            : Entity(situation, currentWindow, 100), enemies(enemies), attackKey(attackKey),
              RightSelectKey(RightSelectKey) {

        entity.setPosition((float) window->getSize().x / 2.0f, (float) window->getSize().y / 1.5f);
        damage = 5;
        initializeHealthBar();
    }


    void update() override {
        if (health >= 0) window->draw(entity);

        if (KeyHandler::getInstance().isKeyTrigger(RightSelectKey)) {
            if (SelectedEnemy + 1 > enemies->size() - 1) SelectedEnemy = 0;
            else SelectedEnemy += 1;
        }

        if (KeyHandler::getInstance().isKeyTrigger(attackKey) && *situation == GameSituation::PLAYER_TURN){
            doDamage(enemies->at(SelectedEnemy));
        }
    }

private:
    int SelectedEnemy = 1;
    Keyboard::Key RightSelectKey;
    Keyboard::Key attackKey;
    vector<Entity *> *enemies;
};

#endif //CARD_GAME_PLAYER_H
