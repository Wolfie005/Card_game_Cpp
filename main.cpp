#include <iostream>
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

float width = 1920;
float height = 1080;

string GameState = "Start";

int main() {
    RenderWindow window(sf::VideoMode((int)width,(int)
    height), "Card Combat");
    window.setFramerateLimit(120);



    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    break;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            return 0;
        }




        //clear
        window.clear(Color::Black);


        //update and display
        window.display();

    }
}
