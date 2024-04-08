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
    Player(GameSituation *situation, RenderWindow *currentWindow, Keyboard::Key attackKey, Keyboard::Key HealKey, Keyboard::Key EnergyReplenishKey , Keyboard::Key RightSelectKey,
           vector<Entity *> *enemies, int energyToken)
            : Entity(situation, currentWindow, 100), enemies(enemies), attackKey(attackKey), HealKey(HealKey),EnergyReplenishKey(EnergyReplenishKey),
              RightSelectKey(RightSelectKey) , energyToken(energyToken){

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

        if (enemies->empty()){
            SelectedEnemy = -1;
        }

        if (SelectedEnemy != -1 && KeyHandler::getInstance().isKeyTrigger(attackKey) && *situation == GameSituation::PLAYER_TURN && energyToken - 1 >= 0){
            doDamage(enemies->at(SelectedEnemy));
            energyToken -= 1;
            *situation = GameSituation::ENEMY_TURN;
            cout << energyToken << endl;
        }

        if (KeyHandler::getInstance().isKeyTrigger(RightSelectKey)){
            if (SelectedEnemy + 1 > enemies->size() - 1) SelectedEnemy = 0;
            else SelectedEnemy += 1;
        }

        if (KeyHandler::getInstance().isKeyTrigger(HealKey) && health + 10 <= initialHealth && energyToken - 1 >= 0){
            health += 10;
            energyToken -= 1;
            cout << energyToken << endl;
        }

        if (KeyHandler::getInstance().isKeyTrigger(EnergyReplenishKey) && energyToken + 1 <= 10){
            energyToken += 1;
            cout << energyToken << endl;
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
    int energyToken;
    Keyboard::Key EnergyReplenishKey;
    Keyboard::Key RightSelectKey;
    Keyboard::Key attackKey;
    Keyboard::Key HealKey;
    vector<Entity *> *enemies;
};

#endif //CARD_GAME_PLAYER_H
