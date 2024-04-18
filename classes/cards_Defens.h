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
        /*player.getGuard += Shield.getGuard();
        energyToken -= 1;
        playerAttack.setString("Guard");*/
    }


private:
    Player *player;

};


