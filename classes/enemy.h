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

        Vector2f position = Vector2f(positionX, (float) window->getSize().y / 3.0f);
        entity.setPosition(position);
        Weapon.setDamage(Weapon.getDamage() * (float)GameWave);
        Shield.setGuard(Shield.getGuard() * (float)GameWave);
        initializeHealthBar(ENEMY);
        cout << "enemy Damage:" << Weapon.getDamage() << endl;

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
            player->ResetGuard();
        }

        if (*situation != GameSituation::ENEMY_TURN) return;
        (*enemiesPlayed)++;
        mt19937 *engine = RandomEngine::getInstance().getEngine();
        uniform_int_distribution<> distribution(0, 2);
        int enemyAttackType = distribution(*engine);
        if (enemyAttackType == 0) {
            doDamage(player);
            enemyAttack.setString("Attack");
        }

        if (enemyAttackType == 1) {
            guard += Shield.getGuard();
            enemyAttack.setString("Defend");
        }

        if (enemyAttackType == 2) {
            enemyAttack.setString("Miss");
        }
    }

    bool markedForRemoval() override {
        return health <= 0;
    }

private:
    float InitialPosition;
    Font font;
    Text enemyAttack;
    Player *player;
    vector<Entity *> *enemies;
    int *enemiesPlayed;
};