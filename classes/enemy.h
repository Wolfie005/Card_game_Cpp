#include "SFML/Graphics.hpp"
#include "entity.h"
#include "randomEngine.h"

using namespace sf;
using namespace std;

enum SelectedType{
    SELECTED,
    NOTsELECTED1,
    NOTsELECTED2
};

class Enemy : public Entity {
public:
    Enemy(GameSituation *situation, RenderWindow *currentWindow, float positionX, Player *player,
          vector<Entity *> *enemies, int *enemiesPlayed) :
            Entity(situation, currentWindow, GameWave * 10),
            player(player), enemies(enemies),
            enemiesPlayed(enemiesPlayed) {

        position = Vector2f(positionX, (float) window->getSize().y / 3.0f);
        entity.setPosition(position);
        initialPositionX = entity.getPosition().x;
        initialPositionY = entity.getPosition().y;
        Weapon.setDamage(Weapon.getDamage() * (float)GameWave);
        Shield.setGuard(Shield.getGuard() * (float)GameWave);
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
        window->draw(enemyAttack);

        if (_isSelected && entity.getPosition().y < initialPositionY + 50){
            entity.setPosition(entity.getPosition().x, entity.getPosition().y + 5);
            enemyAttack.setPosition(entity.getPosition().x, entity.getPosition().y - 200);
        }else if (!_isSelected){
            enemyAttack.setPosition(entity.getPosition().x, entity.getPosition().y - 150);
            entity.setPosition(initialPositionX, initialPositionY);
        }

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

    Vector2f position;
    float initialPositionY;
    float initialPositionX;

    Font font;
    Text enemyAttack;
    Player *player;
    vector<Entity *> *enemies;
    int *enemiesPlayed;

};