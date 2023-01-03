//
// Created by Daniel Lieskovský on 3. 1. 2023.
//

#include "../head/game.h"
#include <SFML/Graphics.hpp>

#define WINDOW_X  2000
#define WINDOW_Y  1200

Game::Game() {
}

void Game::renderWindow() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Bulanci");
    sf::Texture texture;
    texture.loadFromFile("../imgs/bulanek.png"/*, sf::IntRect(0,0,100,100)*/);
    texture.setSmooth(true);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(rand() % WINDOW_X, rand() % WINDOW_Y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }


}
