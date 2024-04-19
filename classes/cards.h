#include "SFML/Graphics.hpp"
#include "randomEngine.h"
#include "gameSituation.h"


#ifndef CARD_GAME_CARDS_H
#define CARD_GAME_CARDS_H


using namespace sf;
using namespace std;

enum cardType {
    ATTACK,
    DEFENSE,
    BUFF,
    DEBUFF
};

class Cards {
public:
    Cards(GameSituation *situation, RenderWindow *window, float positionX) : window(window), situation(situation) {

        Card.setSize(Vector2f(150, 250));
        Card.setOrigin(Card.getSize().x / 2, Card.getSize().y / 2);
        Card.setPosition(positionX, positionY);
        Card.setFillColor(Color::Transparent);
        Card.setOutlineColor(Color::White);
        Card.setOutlineThickness(2);

    }

    //virtual void CardAttackType(cardType) = 0;

    void update() {
        if (used) return;
        window->draw(Card);

    }

    bool markedForRemoval(){
        return used;
    }

    void setXPosition(float positionX){
        Card.setPosition(positionX, positionY);
    }

    void setSelectedCard(bool isCardSelected) {
        if (isCardSelected) {
            Card.setSize(Vector2f(200, 300));
        } else {
            Card.setSize(Vector2f(150, 250));
        }
    }

    virtual void use() = 0;


protected:
    RectangleShape Card;
    RenderWindow *window;
    GameSituation *situation;
    float positionY = (float)window->getSize().y - 200;
    bool used = false;
};

#endif //CARD_GAME_CARDS_H
