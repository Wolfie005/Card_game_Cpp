#include "SFML/Graphics.hpp"
#include "randomEngine.h"
#include "gameSituation.h"
#include "cards.h"
#include "entity.h"
#include "player.h"
#include "Item.h"

using namespace sf;
using namespace std;

enum BuffType{
    HEAL,
    REPLENISH
};

class BuffCard : public Cards{
public:
    BuffCard(GameSituation *situation, RenderWindow *window, float positionX, Player *player) : Cards(situation, window, positionX), player(player){

        Card.setOutlineColor(Color::Green);

        mt19937 *engine = RandomEngine::getInstance().getEngine();
        uniform_int_distribution<> distribution(1, 2);
        int BuffTypeDist = distribution(*engine);

        switch (BuffTypeDist) {
            case 1:
                Card.setFillColor(Color::White);
                buffType = BuffType::HEAL;
                break;
            case 2:
                Card.setFillColor(Color::Blue);
                buffType = BuffType::REPLENISH;
                break;

        }

    }

    void use() override{
        if(player->getHealth() + 10 <= player->getInitialHealth() && buffType == BuffType::HEAL && player->getEnergyToken() - 1 >= 0){
            player->setHealth(player->getHealth() + 10);
            player->setEnergyToken(player->getEnergyToken() - 1 );
            player->getPlayerAttack()->setString("Heal");
        }else if (buffType == BuffType::HEAL){
            player->getPlayerAttack()->setString("Health to high");
        }
        if (player->getEnergyToken() + 1 <= 10 && buffType == BuffType::REPLENISH){
            player->setEnergyToken(player->getEnergyToken() + 1);
            player->getPlayerAttack()->setString("Replenish");
        }else if (buffType == BuffType::REPLENISH){
            player->getPlayerAttack()->setString("Already max energy");
        }
        used = true;
    }


private:
    Player *player;
    BuffType buffType;
};

