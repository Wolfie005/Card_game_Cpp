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
    Player(GameSituation *situation, RenderWindow *currentWindow, Keyboard::Key attackKey, Keyboard::Key HealKey,
           Keyboard::Key GuardKey, Keyboard::Key EnergyReplenishKey, Keyboard::Key RightSelectKey,
           vector<Entity *> *enemies, int energyToken)
            : Entity(situation, currentWindow, 100), enemies(enemies), attackKey(attackKey), HealKey(HealKey),
              GuardKey(GuardKey), EnergyReplenishKey(EnergyReplenishKey),
              RightSelectKey(RightSelectKey), energyToken(energyToken) {

        entity.setPosition((float) window->getSize().x / 2.0f, (float) window->getSize().y / 1.5f);
        damage = 5;
        guard = 0;
        initializeHealthBar(PLAYER);
        characterDisplay("../img/character.png");
        if (!font.loadFromFile("../fonts/Roboto-Light.ttf")) {
            cout << "Error loading font";
            exit(1);
        }
        playerAttack.setFont(font);
    }



    void update() override {
        if (GameState == "Game Over") {
            return;
        }

        if (health <= 0) {
            GameState = "Game Over";
        }
        if (*situation == GameSituation::PLAYER_TURN && energyRecieve == 0) {
            energyToken += 3;
            energyRecieve = 1;
        }


        window->draw(entity);
        energyDisplay(energyToken);
        updateCharacterDisplay();

        playerAttack.setOrigin(playerAttack.getGlobalBounds().width / 2, playerAttack.getGlobalBounds().height / 2);
        playerAttack.setPosition(entity.getPosition().x, entity.getPosition().y - 150);
        window->draw(playerAttack);


        if (SelectedEnemy > enemies->size() - 1 && !enemies->empty()) {
            SelectedEnemy = 0;
        }

        if (enemies->empty()) {
            SelectedEnemy = -1;
        }

        if (SelectedEnemy != -1 && KeyHandler::getInstance().isKeyTrigger(attackKey) &&
            *situation == GameSituation::PLAYER_TURN && energyToken - 1 >= 0) {
            doDamage(enemies->at(SelectedEnemy));
            energyToken -= 1;
            for (auto entity: *enemies) {
                entity->ResetGuard();
            }
            playerAttack.setString("Attack");
        }

        if (KeyHandler::getInstance().isKeyTrigger(RightSelectKey)) {
            if (SelectedEnemy + 1 > enemies->size() - 1) SelectedEnemy = 0;
            else SelectedEnemy += 1;
        }

        if (KeyHandler::getInstance().isKeyTrigger(HealKey) && health + 10 <= initialHealth && energyToken - 1 >= 0) {
            health += 10;
            energyToken -= 1;
            playerAttack.setString("Heal");
        }

        if (KeyHandler::getInstance().isKeyTrigger(EnergyReplenishKey) && energyToken + 1 <= 10) {
            energyToken += 1;
            playerAttack.setString("Replenish");
        }

        if (KeyHandler::getInstance().isKeyTrigger(GuardKey)) {
            guard += 10;
            energyToken -= 1;
            playerAttack.setString("Guard");
        }
        if (energyToken == 0) {
            *situation = GameSituation::ENEMY_TURN;
            energyRecieve = 0;
        }


    }

    int getSelected() const {
        return SelectedEnemy;
    }

    bool markedForRemoval() override {
        return false;
    }

    void setSelectedEnemy(int i) {
        SelectedEnemy = i;
    }

private:
    int energyRecieve = 0;
    Font font;
    Text playerAttack;
    int SelectedEnemy = 1;
    int energyToken;
    Keyboard::Key EnergyReplenishKey;
    Keyboard::Key GuardKey;
    Keyboard::Key RightSelectKey;
    Keyboard::Key attackKey;
    Keyboard::Key HealKey;
    vector<Entity *> *enemies;
};

#endif //CARD_GAME_PLAYER_H
