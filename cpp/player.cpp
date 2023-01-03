//
// Created by Daniel Lieskovský on 3. 1. 2023.
//
#include "../head/player.h"

Player::Player() {
}

sf::RectangleShape Player::generatePlayer(int windowX, int windowY, int playerSize, const sf::Texture* pTexture) {

    this->x = rand() % (windowX - playerSize);
    this->y = rand() % (windowY - playerSize);
    this->size = playerSize;

    this->player.setTexture(pTexture);
    this->player.setSize(sf::Vector2f(this->size,this->size));
    this->player.setPosition(this->x, this->y);

    return this->player;
}




