cmake_minimum_required(VERSION 3.27)
project(Card_game)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

set(SFML_VERSION 2.6.1)

FetchContent_Declare(
        SFML
        URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
)

# SFML
option(SFML_BUILD_NETWORK "Build network" OFF)
FetchContent_MakeAvailable(sfml)

add_executable(Card_game main.cpp
        classes/button.h
        classes/player.h
        classes/enemy.h
        classes/entity.h
        classes/KeyHandler.h
        classes/randomEngine.h
        classes/Item.h
)

target_link_libraries(Card_game sfml-system sfml-window sfml-graphics sfml-audio)