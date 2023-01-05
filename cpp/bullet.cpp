//
// Created by Andrej on 04-Jan-23.
//

#include "../head/bullet.h"

Bullet::Bullet(sf::Texture* texture, float positionX, float positionY, float directionX, float directionY, float mSpeed) {
    this->shape.setTexture(*texture);
    this->shape.setPosition(positionX, positionY);
    this->direction.x = directionX;
    this->direction.y = directionY;
    this->speed = mSpeed;

}

Bullet::~Bullet() {

}

int Bullet::getDirectionBullet() const {
    return directionBullet;
}

void Bullet::setDirectionBullet(int directionBullet) {
    Bullet::directionBullet = directionBullet;
}

void Bullet::update() {
    this->shape.move(this->speed * this->direction);
}

void Bullet::render(sf::RenderTarget *target) {
    target->draw(this->shape);
}

const sf::FloatRect Bullet::getBounds() const {
    return this->shape.getGlobalBounds();
}


