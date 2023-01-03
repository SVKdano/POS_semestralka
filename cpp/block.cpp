//
// Created by Andrej on 03-Jan-23.
//

#include "../head/block.h"

Block::Block() {
    initBlock(0, 0, 0, 0, nullptr);
}

Block::~Block() {

}

void Block::initBlock(int x, int y, int xP, int yP, const sf::Texture* texture) {
    this->rect.setSize(sf::Vector2f(x,y));
    this->rect.setPosition(xP,yP);
    this->rect.setFillColor(sf::Color::Blue);
}

const sf::RectangleShape &Block::getRect() const {
    return this->rect;
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