#include "SFML/Graphics.hpp"
#include "randomEngine.h"
#include "gameSituation.h"
#include "cards.h"
#include "entity.h"
#include "player.h"
#include "Item.h"

using namespace sf;
using namespace std;

class BuffCard : public Cards{
public:
    BuffCard(GameSituation *situation, RenderWindow *window, float positionX, Player *player) : Cards(situation, window, positionX), player(player){

        Card.setOutlineColor(Color::Green);

    }

    void use() override{
        if(player->getHealth() + 10 <= player->getInitialHealth()){
            player->setHealth(player->getHealth() + 10);
            player->setEnergyToken(player->getEnergyToken() - 1 );
            player->getPlayerAttack()->setString("Heal");
        }else{
            player->getPlayerAttack()->setString("Health to high");
        }

    }

private:
    Player *player;

};

