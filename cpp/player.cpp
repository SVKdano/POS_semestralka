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

sf::RectangleShape Player::generatePlayer(int windowX, int windowY, int playerSize, const sf::Texture pTextures[]) {

    this->x = rand() % (windowX - playerSize);
    this->y = rand() % (windowY - playerSize);
    this->size = playerSize;
    this->direction = 0;
    textures = pTextures;


    this->player.setTexture(&pTextures[0]);
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

bool Player::isAlive() const {
    return alive;
}

void Player::setAlive(bool alive) {
    Player::alive = alive;
}

void Player::move() {
    if (this->direction == 0) {
        this->player.move(0.0f, -7.0f);
        this->player.setTexture(&this->textures[0]);
    }
    if (this->direction == 1) {
        this->player.move(7.0f, 0.0f);
        this->player.setTexture(&this->textures[1]);
    }
    if (this->direction == 2) {
        this->player.move(0.0f, 7.0f);
        this->player.setTexture(&this->textures[2]);
    }
    if (this->direction == 3) {
        this->player.move(-7.0f, 0.0f);
        this->player.setTexture(&this->textures[3]);
    }
}







