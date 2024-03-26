cmake_minimum_required(VERSION 3.27)
project(Card_game)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR  "C:/lib/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6.1 REQUIRED system window graphics network audio)

add_executable(Card_game main.cpp
        classes/button.h
        classes/player.h
        classes/enemies.h)

target_link_libraries(Card_game sfml-system sfml-window sfml-graphics sfml-network sfml-audio)