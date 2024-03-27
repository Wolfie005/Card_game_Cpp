//
// Created by Sebastian Håfström on 2024-03-27.
//

#ifndef CARD_GAME_KEYHANDLER_H
#define CARD_GAME_KEYHANDLER_H

#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

class KeyHandler {
public:
    KeyHandler() {
        resetTriggered();
    };

    ~KeyHandler() = default;

    static KeyHandler &getInstance() {
        static KeyHandler instance;
        return instance;
    }

    void resetTriggered() {
        for (bool &i: key_triggered) i = false;
    }

    bool isKeyTrigger(sf::Keyboard::Key key) {
        if (sf::Keyboard::isKeyPressed(key) && !key_triggered[key]) {
            return (key_triggered[key] = true);
        }
        return false;
    }

    bool key_triggered[Keyboard::KeyCount]{};
};

#endif //CARD_GAME_KEYHANDLER_H
