//
// Created by Andrej on 04-Jan-23.
//
#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

class Bullet {
private:
int directionBullet;
sf::RectangleShape bullet;

public:
    Bullet(int direction, int positionX, int positionY);

    virtual ~Bullet();

    void move();

    void generateBullet(int direction, int positionX, int positionY);

    int getDirectionBullet() const;

    void setDirectionBullet(int directionBullet);

    const sf::RectangleShape &getBullet() const;

    int getPositionX();

    int getPositionY();

    void setBulletPosition(int positionX, int positionY);
};
