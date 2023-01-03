//
// Created by Daniel Lieskovský on 3. 1. 2023.
//


#pragma once
#include <SFML/Graphics.hpp>

class Game {
    private:
        sf::RectangleShape player;
        sf::RectangleShape enemy;

    public:
        Game();
        void renderWindow();
};
