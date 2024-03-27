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

string GameState = "Start";

int main() {
    KeyHandler::getInstance();
    RenderWindow window(VideoMode((int)width,(int)
    height), "Card Combat");
    window.setFramerateLimit(120);
    window.setKeyRepeatEnabled(false);

    GameSituation gameSituation = IDLE;




    //List of all the enemies
    vector<Entity *> enemies;

    Player player(&gameSituation, &window, Keyboard::Key::Space, Keyboard::Key::Right, &enemies);


    for (int i = 0; i < 3; i++) {
        float xPos = ((float) window.getSize().x - (float) window.getSize().x / 3.0f * 2) / 2.0f +
                     (float) i * ((float) window.getSize().x / 3.0f);
        enemies.emplace_back(new Enemy(&gameSituation, &window, xPos, &player));
    }


    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case Event::KeyReleased:
                    KeyHandler::getInstance().key_triggered[event.key.code] = false;
                    break;
                default:
                    break;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)){
            return 0;
        }
        if (KeyHandler::getInstance().isKeyTrigger(Keyboard::Q)){
            gameSituation = ENEMY_TURN;
        }
        if (KeyHandler::getInstance().isKeyTrigger(Keyboard::E)){
            gameSituation = PLAYER_TURN;
        }
        if (KeyHandler::getInstance().isKeyTrigger(Keyboard::I)){
            gameSituation = IDLE;
        }
        //clear
        window.clear(Color::Black);


        //update and display
        for (auto entity: enemies) {
            entity->update();
        }
        player.update();
        window.display();

    }
}
