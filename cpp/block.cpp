//
// Created by Andrej on 03-Jan-23.
//

#include "../head/block.h"

Block::Block() {
    generateBlock(0, 0, 0, 0, nullptr);
}

Block::~Block() {

}

void Block::generateBlock(int x, int y, int xP, int yP, const sf::Texture* texture) {
    this->block.setSize(sf::Vector2f(x, y));
    this->block.setPosition(xP, yP);
    this->block.setFillColor(sf::Color::Blue);
}

const sf::RectangleShape &Block::getBlock() const {
    return this->block;
}

int Block::getX() const {
    return this->x;
}

void Block::setX(int newX) {
    this->x = newX;
}

int Block::getY() const {
    return this->y;
}

void Block::setY(int newY) {
    this->y = newY;
}