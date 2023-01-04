//
// Created by Andrej on 04-Jan-23.
//
#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Bullet {
private:
int directionBullet;
sf::RectangleShape bullet;

//news
sf::Sprite shape;

sf::Vector2f direction;
float speed;

public:
    Bullet(int direction, int positionX, int positionY);

    Bullet(sf::Texture* texture, float positionX, float positionY, float directionX, float directionY, float mSpeed);

    virtual ~Bullet();

    void move();

    void generateBullet(int direction, int positionX, int positionY);

    int getDirectionBullet() const;

    void setDirectionBullet(int directionBullet);

    const sf::RectangleShape &getBullet() const;

    int getPositionX();

    int getPositionY();

    void setBulletPosition(int positionX, int positionY);

    //news
    void update();
    void render(sf::RenderTarget* target);

    const sf::FloatRect getBounds() const;
};
