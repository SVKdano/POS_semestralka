//
// Created by Andrej on 03-Jan-23.
//

#pragma once
#include <SFML/Graphics.hpp>

class Block {
private:
    sf::RectangleShape rect;
    int x;
    int y;

public:
    Block();

    virtual ~Block();

    void initBlock(int x, int y, int xP, int yP, const sf::Texture* texture);

    const sf::RectangleShape& getRect() const;

    int getX() const;

    void setX(int newX);

    int getY() const;

    void setY(int newY);
};
