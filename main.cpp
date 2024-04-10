#include <iostream>
#include "SFML/Graphics.hpp"
#include "./classes/player.h"
#include "./classes/enemy.h"
#include "classes/gameSituation.h"
#include "classes/KeyHandler.h"

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
        enemies->emplace_back(new Enemy(situation, currentWindow, xPos, player, enemies, enemiesPlayed));
    }
}

int main() {
    KeyHandler::getInstance();
    RenderWindow window(VideoMode((int)width,(int)
    height), "Card Combat");
    window.setFramerateLimit(120);
    window.setKeyRepeatEnabled(false);

    GameSituation gameSituation = IDLE;

    //List of all the enemies
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
            enemies.clear();
            enemySpawn(&window, &gameSituation, &enemies, &player, &enemiesPlayed);
            player.setSelectedEnemy(1);
            GameWave += 1;
        }

        if (enemies.empty()) {
            GameState = "Wave";
            gameSituation = PLAYER_TURN;
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
            gameSituation = ENEMY_TURN;
        }
        if (KeyHandler::getInstance().isKeyTrigger(Keyboard::E)) {
            gameSituation = PLAYER_TURN;
        }
        if (KeyHandler::getInstance().isKeyTrigger(Keyboard::I)) {
            gameSituation = IDLE;
        }
        //clear
        window.clear(Color::Black);


        //update and display
        for (int i = 0; i < enemies.size(); ++i) {
            auto entity = enemies[i];
            entity->update();
            entity->updateHealthBar();
            entity->setIsSelected(i == player.getSelected());
        }

        player.updateHealthBar();
        player.update();
        window.display();

    }

}
