//
// Created by Sebastian Håfström on 2024-03-27.
//

#ifndef CARD_GAME_GAMESITUATION_H
#define CARD_GAME_GAMESITUATION_H

using namespace std;
using namespace sf;

enum GameSituation {
    IDLE,
    ENEMY_TURN,
    PLAYER_TURN,
    LOOTING,
    CHOICE,
    CARDS,
    RESETCARDS,
    NEW_CARDS
};
string GameState = "Start";
int GameWave = 0;
int SelectedCard = 0;

bool cardsDeny = true;

#endif //CARD_GAME_GAMESITUATION_H
