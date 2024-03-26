//
// Created by Sebastian Håfström on 2024-03-26.
//

#ifndef CARD_GAME_PLAYER_H
#define CARD_GAME_PLAYER_H

#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

class Player {
public:
    Player(RenderWindow *currentwindow) {
        this->window = currentwindow;

        RectangleShape _player;

        _player.setSize(Vector2f(50, 100));
        _player.setOrigin(_player.getSize().x / 2, _player.getSize().y / 2);
        _player.setFillColor(Color::White);
        _player.setPosition((float) window->getSize().x / 2.0f, (float)window->getSize().y / 1.5f);
        this->player = _player;

    }

    void update() {
        window->draw(player);
    }

private:
    RenderWindow *window;
    RectangleShape player;

};

#endif //CARD_GAME_PLAYER_H
