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
    Player(GameSituation *situation, RenderWindow *currentWindow, Keyboard::Key attackKey, Keyboard::Key HealKey, Keyboard::Key RightSelectKey,
           vector<Entity *> *enemies)
            : Entity(situation, currentWindow, 100), enemies(enemies), attackKey(attackKey), HealKey(HealKey),
              RightSelectKey(RightSelectKey) {

        entity.setPosition((float) window->getSize().x / 2.0f, (float) window->getSize().y / 1.5f);
        damage = 5;
        initializeHealthBar(PLAYER);
    }


    void update() override {
        if (GameState == "Game Over"){
            return;
        }
        if(health <= 0){
            GameState = "Game Over";
        }

        window->draw(entity);


        if (SelectedEnemy > enemies->size() - 1 && !enemies->empty()){
            SelectedEnemy = 0;
        }

        if (enemies->empty()) {
            SelectedEnemy = -1;
        }

        if (SelectedEnemy != -1 && KeyHandler::getInstance().isKeyTrigger(attackKey) && *situation == GameSituation::PLAYER_TURN){
            doDamage(enemies->at(SelectedEnemy));
            *situation = GameSituation::ENEMY_TURN;
        }
        if (KeyHandler::getInstance().isKeyTrigger(RightSelectKey)) {
            if (SelectedEnemy + 1 > enemies->size() - 1) SelectedEnemy = 0;
            else SelectedEnemy += 1;
        }
        if (KeyHandler::getInstance().isKeyTrigger(HealKey) && health + 10 <= initialHealth){
            health += 10;
        }

    }
    bool markedForRemoval() override{
        return false;
    }

    void setSelectedEnemy(int i){
        SelectedEnemy = i;
    }

private:
    int SelectedEnemy = 1;
    Keyboard::Key RightSelectKey;
    Keyboard::Key attackKey;
    Keyboard::Key HealKey;
    vector<Entity *> *enemies;
};

#endif //CARD_GAME_PLAYER_H
