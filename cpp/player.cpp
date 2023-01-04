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

void Player::shoot(std::map<std::string, sf::Texture*> textures) {
    this->bullets.push_back(new Bullet(textures["BULLET"], this->sprite.getPosition().x, this->sprite.getPosition().y, dirBullet.x, dirBullet.y, 15.f));
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

void Player::updatePlayer() {
    this->updateDirBullet();
    this->updateCD();
}

void Player::renderPlayer(sf::RenderTarget &renderTarget) {
    renderTarget.draw(this->sprite);
}

void Player::movePlayer(const float dX, const float dY) {
    this->sprite.move(this->speedOfMovement * dX, this->speedOfMovement * dY);
}

void Player::initTexture() {
    this->texture.loadFromFile("../imgs/BlueDown.png");
}

void Player::initSprite() {
    this->sprite.setTexture(this->texture);
}

const sf::Vector2f &Player::getDirBullet() const {
    return this->dirBullet;
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

const sf::Vector2f &Player::getPosition() const {
    return this->sprite.getPosition();
}

void Player::updateCD() {
    if(this->shootingCD < this->shootingCDMax) {
        this->shootingCD += 1.f;
    }
}

const bool Player::canShoot() {
    if(this->shootingCD >= this->shootingCDMax) {
        this->shootingCD = 0.f;
        return true;
    }
    return false;
}

void Player::initVariables() {
    this->speedOfMovement = 7.f;
    this->dirBullet.x = 0.f;
    this->dirBullet.y = -1.f;
    this->shootingCDMax = 10.f;
    this->shootingCD = 8.f;
}












