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

        const sf::RectangleShape &getPlayer() const;

        int getDirection() const;

        void setDirection(int direction);

        const std::vector<Bullet *> &getBullets() const;

        bool isAlive() const;

        void setAlive(bool alive);

        void shoot(std::map<std::string, sf::Texture*> textures);

        void movePlayer(const float dX, const float dY);
        void updatePlayer();
        void renderPlayer(sf::RenderTarget &renderTarget);
        void updateCD();
        const sf::Vector2f &getDirBullet() const;
        const sf::Vector2f &getPosition() const;
        void updateDirBullet();
        const bool canShoot();
        void updateTexture(sf::Keyboard::Key key);
        void updateBulletPosition();
        const sf::Vector2f &getBulletPosition() const;
};
