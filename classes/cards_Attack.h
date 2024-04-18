#include "SFML/Graphics.hpp"
#include "randomEngine.h"
#include "gameSituation.h"
#include "cards.h"



using namespace sf;
using namespace std;

class AttackCard : public Cards{
public:
    AttackCard(GameSituation *situation, RenderWindow *window, float positionX) : Cards(situation, window, positionX){

        Card.setOutlineColor(Color::Red);

    }

    void use() override{

    }


private:

};


