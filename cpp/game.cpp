//
// Created by Daniel Lieskovský on 3. 1. 2023.
//

#include "../head/game.h"

#define WINDOW_X  2000
#define WINDOW_Y  1200

Game::Game() {
}

void Game::renderWindow() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Bulanci");

    sf::Texture texturePlayOne;
    texturePlayOne.loadFromFile("C:\\CLionProjects\\Bulanci\\imgs\\bulanek.png");

    const sf::Texture *pTexture = &texturePlayOne;

    this->player.setTexture(pTexture);
    this->player.setSize(sf::Vector2f(100.0,100.0));
    this->player.setPosition(rand() % WINDOW_X, rand() % WINDOW_Y);

    this->enemy.setTexture(pTexture);
    this->enemy.setSize(sf::Vector2f(100.0,100.0));
    this->enemy.setPosition(rand() % WINDOW_X, rand() % WINDOW_Y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(this->player);
        window.draw(this->enemy);
        window.display();
    }


}
