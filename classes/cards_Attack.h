#include "SFML/Graphics.hpp"
#include "randomEngine.h"
#include "gameSituation.h"
#include "cards.h"
#include "entity.h"
#include "player.h"
#include "Item.h"


using namespace sf;
using namespace std;

enum AttackType {
    SINGLE,
    DOUBLE,
    SINGLE_ENERGY,
    DOUBLE_ENERGY
};

class AttackCard : public Cards {
public:
    AttackCard(GameSituation *situation, RenderWindow *window, float positionX, Player *player)
            : Cards(situation, window, positionX),
              player(player) {
        Card.setOutlineColor(Color::Red);
        mt19937 *engine = RandomEngine::getInstance().getEngine();
        uniform_int_distribution<> distribution(1, 4);
        int AttackTypeDist = distribution(*engine);
        switch (AttackTypeDist) {
            case 1:
                Card.setFillColor(Color::White);

                attackType = AttackType::SINGLE;
                break;
            case 2:
                Card.setFillColor(Color::Blue);

                attackType = AttackType::DOUBLE;
                break;
            case 3:
                Card.setFillColor(Color::Cyan);

                attackType = AttackType::SINGLE_ENERGY;
                break;
            case 4:
                Card.setFillColor(Color::Magenta);

                attackType = AttackType::DOUBLE_ENERGY;
                break;
        }
    }

    void use() override {
        if (player->getSelected() != -1 && *situation == GameSituation::PLAYER_TURN &&
            player->getEnergyToken() - 1 >= 0 && attackType == AttackType::SINGLE) {
            player->doDamage(player->getEnemies()->at(player->getSelected()));
            player->setEnergyToken(player->getEnergyToken() - 1);
            for (auto entity: *player->getEnemies()) {
                entity->ResetGuard();
            }
            player->getPlayerAttack()->setString("Attack");
        }
        if (player->getSelected() != -1 && *situation == GameSituation::PLAYER_TURN &&
            player->getEnergyToken() - 1 >= 0 && attackType == AttackType::DOUBLE) {
            player->doDamage(player->getEnemies()->at(player->getSelected()));
            player->doDamage(player->getEnemies()->at(player->getSelected()));
            player->setEnergyToken(player->getEnergyToken() - 1);
            for (auto entity: *player->getEnemies()) {
                entity->ResetGuard();
            }
            player->getPlayerAttack()->setString("Double Attack");
        }
        if (player->getSelected() != -1 && *situation == GameSituation::PLAYER_TURN &&
            attackType == AttackType::SINGLE_ENERGY) {
            player->doDamage(player->getEnemies()->at(player->getSelected()));
            for (auto entity: *player->getEnemies()) {
                entity->ResetGuard();
            }
            player->getPlayerAttack()->setString("Energy Attack");
        }
        if (player->getSelected() != -1 && *situation == GameSituation::PLAYER_TURN &&
            attackType == AttackType::DOUBLE_ENERGY) {
            player->doDamage(player->getEnemies()->at(player->getSelected()));
            player->doDamage(player->getEnemies()->at(player->getSelected()));
            for (auto entity: *player->getEnemies()) {
                entity->ResetGuard();
            }
            player->getPlayerAttack()->setString("Energy Double Attack");
        }
        used = true;
    }




private:
    Player *player;
    AttackType attackType;

};


