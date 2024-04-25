#include "SFML/Graphics.hpp"
#include "randomEngine.h"
#include "gameSituation.h"
#include "cards.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "Item.h"


using namespace sf;
using namespace std;

class DebuffCard : public Cards {
public:
    DebuffCard(GameSituation *situation, RenderWindow *window, float positionX, Player *player , Item *weapon) : Cards(
            situation, window, positionX), player(player) ,weapon(weapon) {

        Card.setOutlineColor(Color::Yellow);

    }

    void use() override {
        //enemy do less damage


        //enemy take more damage
        if (weapon->getDamage() == weapon->getInitialDamage() && player->getEnergyToken() - 1 >=0){
            weapon->setDamage(weapon->getInitialDamage() / 0.75f);
            player->setEnergyToken(player->getEnergyToken() - 1);
            player->getPlayerAttack()->setString("Enemy DeBuffed");
        }else{
            player->getPlayerAttack()->setString("Enemy Already DeBuffed");
        }
        used = true;
    }

private:
    Enemy *enemy;
    Player *player;
    Item *weapon;

};

