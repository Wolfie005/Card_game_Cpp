#include "SFML/Graphics.hpp"
#include "entity.h"

using namespace sf;
using namespace std;



class Enemy : public Entity {
public:
    Enemy(GameSituation *situation, RenderWindow *currentWindow, float positionX, Player *player) : Entity(situation, currentWindow, 10),
            player(player){

        entity.setPosition(positionX, (float) window->getSize().y / 3.0f);
        damage = 5;
        initializeHealthBar(NOT);
    }

    void update() override {
        if (health <= 0) return;
        window->draw(entity);
        if (*situation != GameSituation::ENEMY_TURN)return;
        *situation = GameSituation::IDLE;
        for (int i = 0; i < 3; i++) {
            doDamage(player);
        }
    }



private:
    Player *player;
};