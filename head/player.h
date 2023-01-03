//
// Created by Daniel Lieskovský on 3. 1. 2023.
//
#pragma once
#include <SFML/Graphics.hpp>

class Player {
    private:
        sf::RectangleShape player;
        int x;
        int y;
        int size;
    public:
        Player();
        sf::RectangleShape generatePlayer(int windowX, int windowY, int playerSize, const sf::Texture* pTexture);
};
