//
// Created by Andrej on 04-Jan-23.
//

#include "../head/bullet.h"

Bullet::Bullet(int direction, int positionX, int positionY) {
    this->generateBullet(direction, positionX, positionY);
}

Bullet::~Bullet() {
    delete(this);
}

void Bullet::generateBullet(int direction, int positionX, int positionY) {
    this->bullet.setSize(sf::Vector2f(10,5));
    this->bullet.setFillColor(sf::Color::White);
    this->setDirectionBullet(direction);
    if (this->directionBullet == 1){
        this->bullet.setPosition(positionX + 20, positionY);
    } else if (this->directionBullet == 0){
        this->bullet.setPosition(positionX, positionY - 20);
    } else if (this->directionBullet == 2){
        this->bullet.setPosition(positionX, positionY + 20);
    } else if (this->directionBullet == 3){
        this->bullet.setPosition(positionX - 20, positionY);
    }
}

void Bullet::move() {
    if (this->directionBullet == 0) {
        this->bullet.move(0, -20);
    } else if (this->directionBullet == 1) {
        this->bullet.move(20, 0);
    } else if (this->directionBullet == 2) {
        this->bullet.move(0, 20);
    } else if (this->directionBullet == 3) {
        this->bullet.move(-20, 0);
    }
}

int Bullet::getDirectionBullet() const {
    return directionBullet;
}

void Bullet::setDirectionBullet(int directionBullet) {
    Bullet::directionBullet = directionBullet;
}

const sf::RectangleShape &Bullet::getBullet() const {
    return bullet;
}

int Bullet::getPositionX() {
    return this->bullet.getPosition().x;
}

int Bullet::getPositionY() {
    return this->bullet.getPosition().y;
}

void Bullet::setBulletPosition(int positionX, int positionY) {
    this->bullet.setPosition(positionX, positionY);
}