#include "SFML/Graphics.hpp"
#include "randomEngine.h"
#include "gameSituation.h"
#include "cards.h"


using namespace sf;
using namespace std;

class BuffCard : public Cards{
public:
    BuffCard(GameSituation *situation, RenderWindow *window, float positionX) : Cards(situation, window, positionX){

        Card.setOutlineColor(Color::Green);

    }

    void use() override{

    }

private:

};

