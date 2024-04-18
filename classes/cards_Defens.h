#include "SFML/Graphics.hpp"
#include "randomEngine.h"
#include "gameSituation.h"
#include "cards.h"


using namespace sf;
using namespace std;

class DefenseCard : public Cards{
public:
    DefenseCard(GameSituation *situation, RenderWindow *window, float positionX) : Cards(situation, window, positionX){

        Card.setOutlineColor(Color::Blue);

    }


    void use() override{

    }


private:


};


