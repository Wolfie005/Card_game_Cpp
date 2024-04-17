#include <iostream>
#include "SFML/Graphics.hpp"
#include "./classes/player.h"
#include "./classes/enemy.h"
#include "classes/gameSituation.h"
#include "classes/KeyHandler.h"
#include "classes//Item.h"

using namespace sf;
using namespace std;

float width = 1920;
float height = 1080;


void enemySpawn(RenderWindow *currentWindow, GameSituation *situation, vector<Entity *> *enemies, Player *player,
                int *enemiesPlayed) {
    GameState = "Fight";
    for (int i = 0; i < 3; i++) {
        float xPos = ((float) currentWindow->getSize().x - (float) currentWindow->getSize().x / 3.0f * 2) / 2.0f +
                     (float) i * ((float) currentWindow->getSize().x / 3.0f);
        auto *pEnemy = new Enemy(situation, currentWindow, xPos, player, enemies, enemiesPlayed);
        enemies->emplace_back(pEnemy);
    }
}

int main() {
    KeyHandler::getInstance();
    RenderWindow window(VideoMode((int)width,(int)
    height), "Card Combat");
    window.setFramerateLimit(120);
    window.setKeyRepeatEnabled(false);

    GameSituation gameSituation = IDLE;

    Font font;
    if (!font.loadFromFile("../fonts/Roboto-Light.ttf")) {
        cout << "Error loading font";
        exit(1);
    }


    //List of all the enemies
    Text question;
    question.setString("If you want sword click 1, if you want shield click 2");
    question.setFont(font);
    question.setOrigin(question.getGlobalBounds().width / 2, question.getGlobalBounds().height / 2);
    question.setPosition((float) window.getSize().x / 2, (float) window.getSize().y / 2);
    Text question2;
    question2.setString("Do you want this weapon click 1 if yes and 2 if no");
    question2.setFont(font);
    question2.setOrigin(question2.getGlobalBounds().width / 2, question2.getGlobalBounds().height / 2);
    question2.setPosition((float) window.getSize().x / 2, (float) window.getSize().y / 2);
    Text Wave;
    Wave.setFont(font);



    vector<Entity *> enemies;
    int enemiesPlayed = 0;
    Player player(&gameSituation, &window, Keyboard::Key::Space, Keyboard::Key::H, Keyboard::Key::G, Keyboard::Key::U,
                  Keyboard::Key::Right, &enemies, 0);


    while (window.isOpen()) {

        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyReleased:
                    KeyHandler::getInstance().key_triggered[event.key.code] = false;
                    break;
                default:
                    break;
            }
        }

        if (GameState == "Wave") {
            GameWave += 1;
            enemies.clear();
            enemySpawn(&window, &gameSituation, &enemies, &player, &enemiesPlayed);
            player.setSelectedEnemy(1);
            gameSituation = GameSituation::PLAYER_TURN;
        }

        if (enemies.empty()) {
            GameState = "Wave";
            if (GameWave %10 == 0){
                gameSituation = LOOTING;
            }
        }

        for (int i = 0; i < enemies.size(); i++) {
            auto entity = enemies[i];
            if (entity->markedForRemoval()) {
                enemies.erase(enemies.begin() + i);
            }
        }


        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            return 0;
        }
        if (KeyHandler::getInstance().isKeyTrigger(Keyboard::O)) {
            GameState = "Wave";
            gameSituation = PLAYER_TURN;
        }
        if (KeyHandler::getInstance().isKeyTrigger(Keyboard::Q)) {
            gameSituation = LOOTING;
        }
        if (KeyHandler::getInstance().isKeyTrigger(Keyboard::E)) {
            gameSituation = PLAYER_TURN;
        }
        if (KeyHandler::getInstance().isKeyTrigger(Keyboard::I)) {
            gameSituation = IDLE;
        }
        //clear
        window.clear(Color::Black);


        if (gameSituation == GameSituation::LOOTING) {
            window.draw(question);
            if (KeyHandler::getInstance().isKeyTrigger(Keyboard::Num1)) {

                player.setTempItem(new Item(&gameSituation, WeaponType::SWORD, &GameWave));
                gameSituation = GameSituation::CHOICE;
            }
            if (KeyHandler::getInstance().isKeyTrigger(Keyboard::Num2)) {
                player.setTempItem(new Item(&gameSituation, WeaponType::SHIELD, &GameWave));
                gameSituation = GameSituation::CHOICE;
            }

        } else if (gameSituation == GameSituation::CHOICE) {
            Text Weapon;
            Weapon.setString("Damage : " + to_string((int)player.getTempItem()->getDamage()) + " " + "Guard : " + to_string((int)player.getTempItem()->getGuard()));
            Weapon.setFont(font);
            Weapon.setOrigin(Weapon.getGlobalBounds().width / 2, Weapon.getGlobalBounds().height / 2);
            Weapon.setPosition((float) window.getSize().x / 2, (float) window.getSize().y / 2 - 200);
            window.draw(Weapon);
            window.draw(question2);
            if (KeyHandler::getInstance().isKeyTrigger(Keyboard::Num1)) {
                if (player.getTempItemType() == WeaponType::SHIELD) {
                    player.setShield(*player.getTempItem());
                }
                if (player.getTempItemType() == WeaponType::SWORD) {
                    player.setWeapon(*player.getTempItem());
                }
                gameSituation = GameSituation::PLAYER_TURN;
            }

            if (KeyHandler::getInstance().isKeyTrigger(Keyboard::Num2)) {
                gameSituation = GameSituation::PLAYER_TURN;
            }

        } else {
            //update and display
            for (int i = 0; i < enemies.size(); ++i) {
                auto entity = enemies[i];
                entity->update();
                entity->updateHealthBar();
                entity->setIsSelected(i == player.getSelected());
            }
            Wave.setString("Wave : " + to_string(GameWave));
            Wave.setOrigin(Wave.getGlobalBounds().width / 2, Wave.getGlobalBounds().height / 2);
            Wave.setPosition(100, 100);
            window.draw(Wave);
            player.updateHealthBar();
            player.update();
        }


        window.display();
    }

}
