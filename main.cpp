#include <iostream>
#include "SFML/Graphics.hpp"
#include "./classes/player.h"
#include "classes/gameSituation.h"
#include "classes/randomEngine.h"
#include "classes/KeyHandler.h"
#include "classes/Item.h"
#include "classes/cards.h"
#include "classes/cards_Attack.h"
#include "classes/cards_Defens.h"
#include "classes/cards_Debuff.h"
#include "classes/cards_Buff.h"

using namespace sf;
using namespace std;

float width = 1920;
float height = 1080;


void enemySpawn(RenderWindow *currentWindow, GameSituation *situation, vector<Entity *> *enemies, Player *player,
                int *enemiesPlayed) {
    GameState = "Fight";
    for (int i = 0; i < 3; i++) {
        float xPos = ((float) currentWindow->getSize().x - (float) currentWindow->getSize().x / 3.0f * 2) / 2.0f +
                     (float) i * ((float) currentWindow->getSize().x / 3.0f);
        auto *pEnemy = new Enemy(situation, currentWindow, xPos, player, enemies, enemiesPlayed);
        enemies->emplace_back(pEnemy);
    }
}

void createCards(RenderWindow *currentWindow, GameSituation *situation, vector<Cards *> *cards, vector<Cards *> *hand,
                 Player *player) {
    mt19937 *engine = RandomEngine::getInstance().getEngine();
    uniform_int_distribution<> distribution(1, 1);
    int i = hand->size();

    float xPos2 = ((float) currentWindow->getSize().x - 150) - ((float) i * (250));

    int cardTypeDist = distribution(*engine);

    switch (cardTypeDist) {
        case 1:
            cards->emplace_back(new AttackCard(situation, currentWindow, xPos2, player));
            break;
        case 2:
            cards->emplace_back(new DefenseCard(situation, currentWindow, xPos2, player));
            break;
        case 3:
            cards->emplace_back(new BuffCard(situation, currentWindow, xPos2, player));
            break;
        case 4:
            cards->emplace_back(new DebuffCard(situation, currentWindow, xPos2, player, player->getWeapon()));
            break;
        default:
            break;
    }
}

void setHand(vector<Cards *> *cards, vector<Cards *> *hand) {
    mt19937 *engine = RandomEngine::getInstance().getEngine();
    uniform_int_distribution<> distribution(0, cards->size() - 1);
    int i = distribution(*engine);

    auto card = (*cards)[i];

    hand->push_back(card);
    cards->erase(cards->begin() + i);
}


void updatePosition(RenderWindow *currentWindow, vector<Cards *> *hand) {
    for (int i = 0; i < hand->size(); ++i) {
        float _xPos = ((float) currentWindow->getSize().x - 150) - ((float) i * (250));
        auto card = (*hand)[i];
        card->setXPosition(_xPos);
    }
};

void resetCard(vector<Cards *> *DiscardedCards, vector<Cards *> *cards) {
    for (int i = 0; i < DiscardedCards->size(); i++) {
        auto card = (*DiscardedCards)[i];
        if (card->markedForReset()) {
            cards->push_back(card);
            DiscardedCards->erase(DiscardedCards->begin() + i);
        }
    }
};


int main() {
    KeyHandler::getInstance();
    RenderWindow window(VideoMode((int)width,(int)
    height), "Card Combat");
    window.setFramerateLimit(120);
    window.setKeyRepeatEnabled(false);

    GameSituation gameSituation = IDLE;

    Font font;
    if (!font.loadFromFile("../fonts/Roboto-Light.ttf")) {
        cout << "Error loading font";
        exit(1);
    }


    //List of all the enemies
    Text question;
    question.setString("If you want sword click 1, if you want shield click 2");
    question.setFont(font);
    question.setOrigin(question.getGlobalBounds().width / 2, question.getGlobalBounds().height / 2);
    question.setPosition((float) window.getSize().x / 2, (float) window.getSize().y / 2);
    Text question2;
    question2.setString("Do you want this weapon click 1 if yes and 2 if no");
    question2.setFont(font);
    question2.setOrigin(question2.getGlobalBounds().width / 2, question2.getGlobalBounds().height / 2);
    question2.setPosition((float) window.getSize().x / 2, (float) window.getSize().y / 2);
    Text GameOver;
    GameOver.setString("Game Over");
    GameOver.setFont(font);
    GameOver.setOrigin(GameOver.getGlobalBounds().width / 2, GameOver.getGlobalBounds().height / 2);
    GameOver.setPosition((float) window.getSize().x / 2, (float) window.getSize().y / 2);
    Text Wave;
    Wave.setFont(font);


    vector<Entity *> enemies;
    int enemiesPlayed = 0;
    Player player(&gameSituation, &window, Keyboard::Key::Space, Keyboard::Key::H, Keyboard::Key::G, Keyboard::Key::U,
                  Keyboard::Key::Right, Keyboard::Key::Left, &enemies, 0);
    vector<Cards *> cards;
    vector<Cards *> hand;
    vector<Cards *> DiscardedCards;


    while (window.isOpen()) {

        Event event{};
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyReleased:
                    KeyHandler::getInstance().key_triggered[event.key.code] = false;
                    break;
                default:
                    break;
            }
        }



        if (GameState == "Start" && cards.size() <= 9) {
            createCards(&window, &gameSituation, &cards, &hand, &player);
            for (auto card : cards){
            }
        } else if (GameState == "Start" && cards.size() == 10) {
            GameState = "Wave";
        }

        if (GameState == "Wave") {
            GameWave += 1;
            enemies.clear();
            enemySpawn(&window, &gameSituation, &enemies, &player, &enemiesPlayed);
            player.setSelectedEnemy(1);
            gameSituation = GameSituation::PLAYER_TURN;
        }
        if (gameSituation == GameSituation::PLAYER_TURN && hand.size() <= 2) {
            setHand(&cards, &hand);
            updatePosition(&window, &hand);
        }
        if (cards.size() <= 2 && GameState != "Start") {
            gameSituation = CARDS;
        }

        if (gameSituation == GameSituation::CARDS) {
            for (auto DiscardedCard: DiscardedCards) {
                DiscardedCard->setUnmarkedForRemoval();
            }
            gameSituation = RESETCARDS;
        }

        if (gameSituation == GameSituation::RESETCARDS) {
            resetCard(&DiscardedCards, &cards);
            gameSituation = PLAYER_TURN;
        }

        if (enemies.empty() && GameState != "Start") {
            GameState = "Wave";
            if (GameWave % 10 == 0) {
                gameSituation = LOOTING;
            }
        }

        for (int i = 0; i < enemies.size(); i++) {
            auto entity = enemies[i];
            if (entity->markedForRemoval()) {
                enemies.erase(enemies.begin() + i);
            }
        }

        for (int i = 0; i < hand.size(); i++) {
            auto card = hand[i];
            if (card->markedForRemoval()) {
                DiscardedCards.push_back(card);
                hand.erase(hand.begin() + i);
                cout << DiscardedCards.size() << endl;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            return 0;
        }

        if (GameState != "Game Over"){

            if (KeyHandler::getInstance().isKeyTrigger(Keyboard::A)) {
                if (SelectedCard + 1 > hand.size() - 1) SelectedCard = 0;
                else SelectedCard += 1;
            }

            if (KeyHandler::getInstance().isKeyTrigger(Keyboard::D)) {
                if (SelectedCard - 1 < 0) SelectedCard = 2;
                else SelectedCard -= 1;
            }

            if (KeyHandler::getInstance().isKeyTrigger(Keyboard::Q)) {
                gameSituation = LOOTING;
            }

            if (KeyHandler::getInstance().isKeyTrigger(Keyboard::Space)) {
                hand.at(SelectedCard)->use();
            }
        }else{
            if (KeyHandler::getInstance().isKeyTrigger(Keyboard::R)){
                GameWave = 0;
                GameState = "Start";
                player.getWeapon()->setDefaultWeapon();
                player.getShield()->setDefaultShield();
                player.getPlayerAttack()->setString("");
                player.resetHealth();
            }
        }



        //clear
        window.clear(Color::Black);

    if (GameState == "Game Over"){
        window.draw(GameOver);

        }else if (gameSituation == GameSituation::LOOTING) {
            window.draw(question);
            if (KeyHandler::getInstance().isKeyTrigger(Keyboard::Num1)) {

                player.setTempItem(new Item(&gameSituation, WeaponType::SWORD, &GameWave));
                gameSituation = GameSituation::CHOICE;
            }
            if (KeyHandler::getInstance().isKeyTrigger(Keyboard::Num2)) {
                player.setTempItem(new Item(&gameSituation, WeaponType::SHIELD, &GameWave));
                gameSituation = GameSituation::CHOICE;
            }

        } else if (gameSituation == GameSituation::CHOICE) {
            Text Weapon;
            Weapon.setString("Damage : " + to_string((int) player.getTempItem()->getDamage()) + " " + "Guard : " +
                             to_string((int) player.getTempItem()->getGuard()));
            Weapon.setFont(font);
            Weapon.setOrigin(Weapon.getGlobalBounds().width / 2, Weapon.getGlobalBounds().height / 2);
            Weapon.setPosition((float) window.getSize().x / 2, (float) window.getSize().y / 2 - 200);
            window.draw(Weapon);
            window.draw(question2);
            if (KeyHandler::getInstance().isKeyTrigger(Keyboard::Num1)) {
                if (player.getTempItemType() == WeaponType::SHIELD) {
                    player.setShield(*player.getTempItem());
                }
                if (player.getTempItemType() == WeaponType::SWORD) {
                    player.setWeapon(*player.getTempItem());
                }
                gameSituation = GameSituation::PLAYER_TURN;
            }

            if (KeyHandler::getInstance().isKeyTrigger(Keyboard::Num2)) {
                gameSituation = GameSituation::PLAYER_TURN;
            }

        } else {
            //update and display
            for (int i = 0; i < enemies.size(); ++i) {
                auto entity = enemies[i];
                entity->update();
                entity->updateHealthBar();
                entity->setIsSelected(i == player.getSelected());
            }
            for (int i = 0; i < hand.size(); ++i) {
                auto card = hand[i];
                card->update();
                card->setSelectedCard(i == SelectedCard);
            }

            Wave.setString("Wave : " + to_string(GameWave));
            Wave.setOrigin(Wave.getGlobalBounds().width / 2, Wave.getGlobalBounds().height / 2);
            Wave.setPosition(100, 100);
            window.draw(Wave);
            player.updateHealthBar();
            player.update();
        }


        window.display();
    }

}
