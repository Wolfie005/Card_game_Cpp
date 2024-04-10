#include "SFML/Graphics.hpp"
#include "entity.h"
#include "randomEngine.h"

using namespace sf;
using namespace std;


class Enemy : public Entity {
public:
    Enemy(GameSituation *situation, RenderWindow *currentWindow, float positionX, Player *player,
          vector<Entity *> *enemies, int *enemiesPlayed) :
            Entity(situation, currentWindow, GameWave * 10),
            player(player), enemies(enemies),
            enemiesPlayed(enemiesPlayed) {

        entity.setPosition(positionX, (float) window->getSize().y / 3.0f);
        damage = 5.0f * (float) GameWave;
        guard = 0;
        initializeHealthBar(ENEMY);

        if (!font.loadFromFile("../fonts/Roboto-Light.ttf")) {
            cout << "Error loading font";
            exit(1);
        }
        enemyAttack.setFont(font);
    }

    void update() override {
        if (health <= 0) return;
        window->draw(entity);

        enemyAttack.setOrigin(enemyAttack.getGlobalBounds().width / 2, enemyAttack.getGlobalBounds().height / 2);
        enemyAttack.setPosition(entity.getPosition().x, entity.getPosition().y - 150);
        window->draw(enemyAttack);

        if (*enemiesPlayed == enemies->size()) {
            *situation = GameSituation::PLAYER_TURN;
            *enemiesPlayed = 0;
        }
        if (*situation != GameSituation::ENEMY_TURN) return;
        (*enemiesPlayed)++;
        mt19937 &engine = RandomEngine::getInstance().getEngine();
        uniform_int_distribution<> distribution(0, 2);
        int enemyAttackType = distribution(engine);
        if (enemyAttackType == 0) {
            doDamage(player);
            enemyAttack.setString("Attack");
            cout << "enemy" << endl;
            cout << health << endl << guard << endl;
        }

        if (enemyAttackType == 1) {
            guard += 10;
            enemyAttack.setString("Defend");
            cout << "enemy" << endl;
            cout << health << endl << guard << endl;
        }

        if (enemyAttackType == 2) {
            enemyAttack.setString("Miss");
            cout << "enemy" << endl;
            cout << health << endl << guard << endl;
        }
    }

    bool markedForRemoval() override {
        return health <= 0;
    }

private:
    Font font;
    Text enemyAttack;
    Player *player;
    vector<Entity *> *enemies;
    int *enemiesPlayed;

};