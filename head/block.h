//
// Created by Andrej on 03-Jan-23.
//

#pragma once
#include <SFML/Graphics.hpp>

class Block {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;


public:
    Block(sf::Texture* texture, float posX, float posY);

    virtual ~Block();

    const sf::RectangleShape& getBlock() const;

    void renderBlock(sf::RenderTarget *renderTarget);

    const sf::FloatRect getBounds() const;
};
