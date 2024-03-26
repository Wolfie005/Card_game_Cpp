//
// Created by Sebastian Håfström on 2024-03-26.
//

#ifndef CARD_GAME_ENEMY_H
#define CARD_GAME_ENEMY_H

#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

class Enemies {
public:
    Enemies(RenderWindow *currentwindow, int health) {
        this->window = currentwindow;

        RectangleShape _enemy;

        _enemy.setSize(Vector2f(50, 100));
        _enemy.setOrigin(_enemy.getSize().x / 2, _enemy.getSize().y / 2);
        _enemy.setFillColor(Color::White);
        _enemy.setPosition((float) window->getSize().x / 2.0f, (float)window->getSize().y / 3.0f);
        this->enemy = _enemy;

    }

    void update() {
        window->draw(enemy);
    }

private:
    RenderWindow *window;
    RectangleShape enemy;

};


#endif //CARD_GAME_ENEMY_H
