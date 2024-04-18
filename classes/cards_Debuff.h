#include "SFML/Graphics.hpp"
#include "randomEngine.h"
#include "gameSituation.h"
#include "cards.h"


using namespace sf;
using namespace std;

class DebuffCard : public Cards{
public:
    DebuffCard(GameSituation *situation, RenderWindow *window, float positionX) : Cards(situation, window, positionX){

        Card.setOutlineColor(Color::Yellow);

    }

    void use() override{

    }

private:

};

