//
// Created by Daniel Lieskovský on 3. 1. 2023.
//
#include "../head/player.h"
#include <unistd.h>

Player::Player(bool isBlue) {
    this->blue = isBlue;
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
    if (blue)
        this->texture.loadFromFile("../imgs/BlueDown.png");
    if (!blue)
        this->texture.loadFromFile("../imgs/RedDown.png");
}

void Player::initSprite() {
    if (blue) {
        this->sprite.setPosition(100, (rand() % (800 - 100)));
    } else {
        this->sprite.setPosition(1050, (rand() % (800 - 100)));
    }
    this->sprite.setTexture(this->texture);
}

void Player::initVariables() {
    this->speedOfMovement = 7.f;
    this->dirBullet.x = 0.f;
    this->dirBullet.y = -1.f;
    this->shootingCDMax = 10.f;
    this->shootingCD = 8.f;
    this->bulletPosition.x = this->position.x + 50.f;
    this->bulletPosition.y = this->position.y - 6.f;
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

int Player::getDirection() const {
    return direction;
}


void Player::setDirection(int direction) {
    Player::direction = direction;
}

void Player::movePlayer(const float dX, const float dY) {
    this->sprite.move(this->speedOfMovement * dX, this->speedOfMovement * dY);
}

void Player::respawn() {
    if (this->blue) {
        this->sprite.setPosition(100, ((rand() % 600) + 100));
        this->texture.loadFromFile("../imgs/BlueDown.png");
        this->sprite.setTexture(this->texture);
        if (this->lives <= 0 ) {
            this->texture.loadFromFile("../imgs/BlueDead.png");
        }

    } else
    {
        this->sprite.setPosition(1050, ((rand() % 600) + 100));
        this->texture.loadFromFile("../imgs/RedDown.png");
        this->sprite.setTexture(this->texture);
        if (this->lives <= 0 ) {
            this->texture.loadFromFile("../imgs/RedDead.png");
        }
    }
    this->direction = 2;
}

void Player::updatePlayer() {
    this->updateDirBullet();
    updateBulletPosition();
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

void Player::updateTexture() {
    if (blue) {
        if (this->direction == 0) {
            this->texture.loadFromFile("../imgs/BlueUp.png");
        } else if (this->direction == 1) {
            this->texture.loadFromFile("../imgs/BlueRight.png");
        } else if (this->direction == 2) {
            this->texture.loadFromFile("../imgs/BlueDown.png");
        } else if (this->direction == 3) {
            this->texture.loadFromFile("../imgs/BlueLeft.png");
        }
    }

    if (!blue) {
        if (this->direction ==0) {
            this->texture.loadFromFile("../imgs/RedUp.png");
        } else if (this->direction == 1) {
            this->texture.loadFromFile("../imgs/RedRight.png");
        } else if (this->direction == 2) {
            this->texture.loadFromFile("../imgs/RedDown.png");
        } else if (this->direction == 3) {
            this->texture.loadFromFile("../imgs/RedLeft.png");
        }
    }
}

void Player::updateBulletPosition() {
    if (this->direction == 0) {
        this->bulletPosition.x = this->sprite.getPosition().x + 50.f;
        this->bulletPosition.y = this->sprite.getPosition().y - 6.f;
    } else if (this->direction == 1) {
        this->bulletPosition.x = this->sprite.getPosition().x + 106.f;
        this->bulletPosition.y = this->sprite.getPosition().y + 50.f;
    } else if (this->direction == 2) {
        this->bulletPosition.x = this->sprite.getPosition().x + 50.f;
        this->bulletPosition.y = this->sprite.getPosition().y + 106.f;
    } else {
        this->bulletPosition.x = this->sprite.getPosition().x - 6.f;
        this->bulletPosition.y = this->sprite.getPosition().y + 50.f;
    }
}

const sf::Vector2f &Player::getBulletPosition() const {
    return bulletPosition;
}

void Player::setPosition(const float posX, const float posY) {
    this->sprite.setPosition(posX, posY);
}

void Player::setPosition(const sf::Vector2f &position) {
    this->sprite.setPosition(position);
}

const sf::FloatRect Player::getBounds() const {
    return this->sprite.getGlobalBounds();
}

void Player::setLives(int lives) {
    this->lives = lives;
}

int Player::getLives() {
    return this->lives;
}

void Player::setSpeedOfMovement(int speed) {
    this->speedOfMovement = 0;
}


















