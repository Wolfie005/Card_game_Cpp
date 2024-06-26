//
// Created by Sebastian Håfström on 2024-03-26.
//

#ifndef CARD_GAME_PLAYER_H
#define CARD_GAME_PLAYER_H

#include "SFML/Graphics.hpp"
#include "entity.h"
#include "KeyHandler.h"
#include "Item.h"


using namespace sf;
using namespace std;

class Player : public Entity {
public:
    Player(GameSituation *situation, RenderWindow *currentWindow, Keyboard::Key attackKey, Keyboard::Key HealKey,
           Keyboard::Key GuardKey, Keyboard::Key EnergyReplenishKey, Keyboard::Key RightSelectKey, Keyboard::Key LeftSelectKey,
           vector<Entity *> *enemies, int energyToken)
            : Entity(situation, currentWindow, 100), enemies(enemies), attackKey(attackKey), HealKey(HealKey),
              GuardKey(GuardKey), EnergyReplenishKey(EnergyReplenishKey),
              RightSelectKey(RightSelectKey), LeftSelectKey(LeftSelectKey), energyToken(energyToken) {

        position = Vector2f((float)window->getSize().x / 2.0f, (float) window->getSize().y / 1.5f);
        entity.setPosition(position);
        guard = 0;
        initializeHealthBar(PLAYER);
        characterDisplay("../img/character.png", "../img/sword.png", "../img/shield.png");
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

/*        if (SelectedEnemy != -1 && KeyHandler::getInstance().isKeyTrigger(attackKey)) {
            doDamage(enemies->at(SelectedEnemy));
            energyToken -= 1;
            for (auto entity: *enemies) {
                entity->ResetGuard();
            }
            playerAttack.setString("Attack");
        }

        if (SelectedEnemy != -1 && *situation == GameSituation::PLAYER_TURN && energyToken - 1 >= 0) {

        }*/

        if (KeyHandler::getInstance().isKeyTrigger(RightSelectKey)) {
            if (SelectedEnemy + 1 > enemies->size() - 1) SelectedEnemy = 0;
            else SelectedEnemy += 1;
        }
        if (KeyHandler::getInstance().isKeyTrigger(LeftSelectKey)) {
            if (SelectedEnemy - 1 < 0) SelectedEnemy = 2;
            else SelectedEnemy -= 1;
        }

       /* if (KeyHandler::getInstance().isKeyTrigger(HealKey) && health + 10 <= initialHealth && energyToken - 1 >= 0) {
            health += 10;
            energyToken -= 1;
            playerAttack.setString("Heal");
        }*/

       /* if (KeyHandler::getInstance().isKeyTrigger(EnergyReplenishKey) && energyToken + 1 <= 10) {
            energyToken += 1;
            playerAttack.setString("Replenish");
        }*/

       /* if (KeyHandler::getInstance().isKeyTrigger(GuardKey) && energyToken - 1 >= 0) {
            guard += Shield.getGuard();
            energyToken -= 1;
            playerAttack.setString("Guard");
        }*/
        if (energyToken == 0) {
            *situation = GameSituation::ENEMY_TURN;
            getWeapon()->setDamage(getWeapon()->getInitialDamage());
            energyRecieve = 0;
        }


    }

    Keyboard::Key getAttackKey() const {
        return attackKey;
    }

    void setAttackKey(Keyboard::Key attackKey) {
        Player::attackKey = attackKey;
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

    vector<Entity *> *getEnemies() const {
        return enemies;
    }

    void setEnemies(vector<Entity *> *newEnemies) {
        enemies = newEnemies;
    }

    int getEnergyToken() const {
        return energyToken;
    }

    void setEnergyToken(int newEnergyToken) {
        energyToken = newEnergyToken;
    }

    Text *getPlayerAttack() {
        return &playerAttack;
    }

    const Vector2f &getPosition() const {
        return position;
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
    Keyboard::Key LeftSelectKey;
    Keyboard::Key attackKey;
    Keyboard::Key HealKey;
    vector<Entity *> *enemies;
    Vector2f position;
};

#endif //CARD_GAME_PLAYER_H
