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
        const sf::Texture* textures;
        int direction = 2;
        int lives = 3;

        sf::Sprite sprite;
        sf::Texture texture;

        sf::Vector2f dirBullet;
        sf::Vector2f bulletPosition;
        sf::Vector2f position;

        float speedOfMovement;
        float shootingCD;
        float shootingCDMax;

        bool blue = true;

        void initTexture();
        void initSprite();
        void initVariables();

    public:
        Player(bool isBlue);

        virtual ~Player();

        int getDirection() const;

        void setDirection(int direction);


        void movePlayer(const float dX, const float dY);
        void updatePlayer();
        void renderPlayer(sf::RenderTarget &renderTarget);

        const sf::Vector2f &getDirBullet() const;
        const sf::Vector2f &getPosition() const;

        void updateCD();
        void updateDirBullet();
        const bool canShoot();
        const sf::Vector2f &getBulletPosition() const;

        void updateBulletPosition();
        void updateTexture();

        void setPosition(const float posX, const float posY);
        void setPosition(const sf::Vector2f &position);

        const sf::FloatRect getBounds() const;

        void respawn();
        int getLives();
        void setLives(int lives);
        void setSpeedOfMovement(int speed);
};
