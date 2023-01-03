//
// Created by Andrej on 03-Jan-23.
//

#pragma once
#include <SFML/Graphics.hpp>

class Block {
private:
    sf::RectangleShape block;
    int x;
    int y;

public:
    Block();

    virtual ~Block();

    void generateBlock(int x, int y, int xP, int yP, const sf::Texture* texture);

    const sf::RectangleShape& getBlock() const;

    int getX() const;

    void setX(int newX);

    int getY() const;

    void setY(int newY);
};
