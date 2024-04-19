#include "SFML/Graphics.hpp"
#include "randomEngine.h"
#include "gameSituation.h"
#include "cards.h"
#include "entity.h"
#include "player.h"
#include "Item.h"


using namespace sf;
using namespace std;

class DefenseCard : public Cards{
public:
    DefenseCard(GameSituation *situation, RenderWindow *window, float positionX, Player *player) : Cards(situation, window, positionX), player(player){

        Card.setOutlineColor(Color::Blue);

    }


    void use() override{
        player->setGuard(player->getGuard() + player->getShield()->getGuard());
        player->setEnergyToken(player->getEnergyToken() - 1);
        player->getPlayerAttack()->setString("Guard");
        used = true;
    }



private:
    Player *player;

};


