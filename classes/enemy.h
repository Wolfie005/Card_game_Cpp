#include "SFML/Graphics.hpp"
#include "entity.h"

using namespace sf;
using namespace std;



class Enemy : public Entity {
public:
    [[maybe_unused]]
    explicit Enemy(GameSituation *situation, RenderWindow *currentWindow, float positionX) : Entity(situation, currentWindow, 10) {

        entity.setPosition(positionX, (float) window->getSize().y / 3.0f);

    }

    void update() override {
        if (health > 0) {
            window->draw(entity);
        }
    }



private:

};

