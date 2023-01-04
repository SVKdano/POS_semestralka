//
// Created by Daniel Lieskovský on 3. 1. 2023.
//
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "bullet.h"

class Player {
    private:
        sf::RectangleShape player;
        std::vector<Bullet*> bullets;
        const sf::Texture* textures;
        int x;
        int y;
        int size;
        int direction;
        bool alive = true;

        //news
        sf::Sprite sprite;
        sf::Texture texture;

        float speedOfMovement;

        void initTexture();
        void initSprite();

    public:
        Player();

        virtual ~Player();

        sf::RectangleShape generatePlayer(int windowX, int windowY, int playerSize, const sf::Texture pTextures[]);

        const sf::RectangleShape &getPlayer() const;

        int getDirection() const;

        void setDirection(int direction);

        const std::vector<Bullet *> &getBullets() const;

        bool isAlive() const;

        void setAlive(bool alive);

        void shoot();

        void move();

        //news
        void movePlayer(const float dX, const float dY);
        void updatePlayer();
        void renderPlayer(sf::RenderTarget &renderTarget);
};
