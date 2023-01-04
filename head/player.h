//
// Created by Daniel Lieskovský on 3. 1. 2023.
//
#pragma once
#include <SFML/Graphics.hpp>
#include "bullet.h"

class Player {
    private:
        sf::RectangleShape player;
        std::vector<Bullet*> bullets;
        int x;
        int y;
        int size;
        int direction;

    public:
        Player();

        virtual ~Player();

        sf::RectangleShape generatePlayer(int windowX, int windowY, int playerSize, const sf::Texture* pTexture);

        const sf::RectangleShape &getPlayer() const;

        int getDirection() const;

        void setDirection(int direction);

        const std::vector<Bullet *> &getBullets() const;

        void shoot();
};
