//
// Created by Sebastian Håfström on 2024-04-09.
//
#include "random"

#ifndef CARD_GAME_RANDOMENGINE_H
#define CARD_GAME_RANDOMENGINE_H

using namespace std;

/*
 To use the engine type
 mt19937 &engine = RandomEngine::getInstance().getEngine();
 uniform_int_distribution<> distribution (number, number);
 int variableName = distribution(engine);
 */

class RandomEngine{
public:
    static RandomEngine &getInstance(){
        static RandomEngine instance;
        return instance;
    }

    mt19937 *getEngine(){
        return &this->engine;
    }

    RandomEngine(const RandomEngine &) = delete;
    RandomEngine &operator=(const RandomEngine &) = delete;
private:
    random_device randomDevice;
    mt19937 engine;

    RandomEngine() : engine(randomDevice()){};
};

#endif //CARD_GAME_RANDOMENGINE_H
