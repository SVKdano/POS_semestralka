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

//news
sf::Sprite shape;
sf::Vector2f direction;
float speed;

public:
    Bullet(sf::Texture* texture, float positionX, float positionY, float directionX, float directionY, float mSpeed);

    virtual ~Bullet();

    int getDirectionBullet() const;

    void setDirectionBullet(int directionBullet);

    void update();

    void render(sf::RenderTarget* target);

    const sf::FloatRect getBounds() const;
};
