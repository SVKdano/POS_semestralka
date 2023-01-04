//
// Created by Daniel Lieskovský on 3. 1. 2023.
//
#include "../head/player.h"

Player::Player() {
}

Player::~Player() {
    for (auto &bullet : this->bullets) {
        delete bullet;
    }
}

sf::RectangleShape Player::generatePlayer(int windowX, int windowY, int playerSize, const sf::Texture* pTexture) {

    this->x = rand() % (windowX - playerSize);
    this->y = rand() % (windowY - playerSize);
    this->size = playerSize;
    this->direction = rand() % 4;

    this->player.setTexture(pTexture);
    this->player.setSize(sf::Vector2f(this->size,this->size));
    this->player.setPosition(this->x, this->y);

    return this->player;
}

int Player::getDirection() const {
    return direction;
}

void Player::setDirection(int direction) {
    Player::direction = direction;
}

void Player::shoot() {
    Bullet* bullet;
    bullet = new Bullet(this->direction,this->getPlayer().getPosition().x,this->getPlayer().getPosition().y);
    this->bullets.push_back(bullet);
}

const std::vector<Bullet *> &Player::getBullets() const {
    return bullets;
}

const sf::RectangleShape &Player::getPlayer() const {
    return player;
}





