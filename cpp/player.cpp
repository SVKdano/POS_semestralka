//
// Created by Daniel Lieskovský on 3. 1. 2023.
//
#include "../head/player.h"

Player::Player() {
    this->initTexture();
    this->initSprite();
    this->initVariables();
}

Player::~Player() {
    for (auto *bullet : this->bullets) {
        delete bullet;
    }
}

void Player::initTexture() {
    this->texture.loadFromFile("../imgs/BlueDown.png");
}

void Player::initSprite() {
    this->sprite.setTexture(this->texture);
}

void Player::initVariables() {
    this->speedOfMovement = 7.f;
    this->dirBullet.x = 0.f;
    this->dirBullet.y = -1.f;
    this->shootingCDMax = 10.f;
    this->shootingCD = 8.f;
}

void Player::renderPlayer(sf::RenderTarget &renderTarget) {
    renderTarget.draw(this->sprite);
}

const sf::Vector2f &Player::getPosition() const {
    return this->sprite.getPosition();
}

const sf::Vector2f &Player::getDirBullet() const {
    return this->dirBullet;
}

const bool Player::canShoot() {
    if(this->shootingCD >= this->shootingCDMax) {
        this->shootingCD = 0.f;
        return true;
    }
    return false;
}

const std::vector<Bullet *> &Player::getBullets() const {
    return bullets;
}

const sf::RectangleShape &Player::getPlayer() const {
    return player;
}

int Player::getDirection() const {
    return direction;
}

bool Player::isAlive() const {
    return alive;
}

void Player::setAlive(bool alive) {
    Player::alive = alive;
}

void Player::setDirection(int direction) {
    Player::direction = direction;
}

void Player::shoot(std::map<std::string, sf::Texture*> textures) {
    this->bullets.push_back(new Bullet(textures["BULLET"], this->sprite.getPosition().x, this->sprite.getPosition().y, dirBullet.x, dirBullet.y, 15.f));
}

void Player::movePlayer(const float dX, const float dY) {
    this->sprite.move(this->speedOfMovement * dX, this->speedOfMovement * dY);
}

void Player::updatePlayer() {
    this->updateDirBullet();
    this->updateCD();
}

void Player::updateDirBullet() {
    if (this->direction == 0) {
        this->dirBullet.x = 0.f;
        this->dirBullet.y = -1.f;
    }
    if (this->direction == 1) {
        this->dirBullet.x = 1.f;
        this->dirBullet.y = 0.f;
    }
    if (this->direction == 2) {
        this->dirBullet.x = 0.f;
        this->dirBullet.y = 1.f;
    }
    if (this->direction == 3) {
        this->dirBullet.x = -1.f;
        this->dirBullet.y = 0.f;
    }
}

void Player::updateCD() {
    if(this->shootingCD < this->shootingCDMax) {
        this->shootingCD += 1.f;
    }
}

void Player::updateTexture(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Key::W) {
        this->direction = 0;
        this->texture.loadFromFile("../imgs/BlueUp.png");
    } else if (key == sf::Keyboard::Key::D) {
        this->direction = 1;
        this->texture.loadFromFile("../imgs/BlueRight.png");
    } else if (key == sf::Keyboard::Key::S) {
        this->direction = 2;
        this->texture.loadFromFile("../imgs/BlueDown.png");
    } else if (key == sf::Keyboard::Key::A){
        this->direction = 3;
        this->texture.loadFromFile("../imgs/BlueLeft.png");
    }
}













