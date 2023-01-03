//
// Created by Daniel Lieskovský on 3. 1. 2023.
//


#pragma once
#include <SFML/Graphics.hpp>
#include "block.h"

class Game {
    private:
        sf::RectangleShape player;
        sf::RectangleShape enemy;
        Block block;
    public:
        Game();
        void renderWindow();

};
