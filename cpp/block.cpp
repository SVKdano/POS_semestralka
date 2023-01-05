//
// Created by Andrej on 03-Jan-23.
//

#include "../head/block.h"

Block::Block(sf::Texture* texture, float posX, float posY) {
    this->sprite.setTexture(*texture);
    this->sprite.setPosition(posX, posY);
}

Block::~Block() {

}

void Block::renderBlock(sf::RenderTarget *renderTarget) {
    renderTarget->draw(this->sprite);
}

const sf::FloatRect Block::getBounds() const {
    return this->sprite.getGlobalBounds();
}
