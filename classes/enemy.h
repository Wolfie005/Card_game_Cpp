#include "SFML/Graphics.hpp"
#include "entity.h"
#include "randomEngine.h"

using namespace sf;
using namespace std;


class Enemy : public Entity {
public:
    Enemy(GameSituation *situation, RenderWindow *currentWindow, float positionX, Player *player, vector<Entity *> *enemies) : Entity(situation, currentWindow, GameWave * 10),
            player(player), enemies(enemies) {

        entity.setPosition(positionX, (float) window->getSize().y / 3.0f);
        damage = 5.0f * (float)GameWave;
        guard = 0;
        initializeHealthBar(ENEMY);

    }

    void update() override {
        if (health <= 0) return;
        window->draw(entity);

        if (*situation != GameSituation::ENEMY_TURN) return;
        *situation = GameSituation::PLAYER_TURN;
        mt19937 &engine = RandomEngine::getInstance().getEngine();
        uniform_int_distribution<> distribution(0, 2);
        for (int i = 0; i < enemies->size(); i++) {
            int enemyAttackType = distribution(engine);
            if (enemyAttackType == 0) {
                doDamage(player);
                cout << "attack" << endl;
                cout << health <<endl << guard<< endl;
            }

            if (enemyAttackType == 1) {
                guard += 10;
                cout << "defend" << endl;
                cout << health <<endl << guard<< endl;
            }

            if (enemyAttackType == 2){
                cout << "miss" << endl;
                cout << health <<endl << guard<< endl;
            }
        }

    }

    bool markedForRemoval() override{
        return health <= 0;
    }

private:
    Player *player;
    vector<Entity *> *enemies;
};