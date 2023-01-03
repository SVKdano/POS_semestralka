//
// Created by Daniel Lieskovský on 3. 1. 2023.
//

#include "../head/game.h"

#define WINDOW_X  1200
#define WINDOW_Y  800
#define TEXTURE_SIZE 100

Game::Game() {
}

void Game::render() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Bulanci");
    sf::Vector2f movement;

    sf::Texture texturePlayer[2];
    texturePlayer[0].loadFromFile("../imgs/bulanek.png");
    texturePlayer[1].loadFromFile("../imgs/bulanekEnemy.png");

    const sf::Texture *pTextureOne = &texturePlayer[0];
    const sf::Texture *pTextureTwo = &texturePlayer[1];

    sf::RectangleShape playerClassROne = this->playerClass
            .generatePlayer(WINDOW_X,WINDOW_Y,TEXTURE_SIZE,pTextureOne);

    sf::RectangleShape playerClassRTwo = this->playerClass
            .generatePlayer(WINDOW_X,WINDOW_Y,TEXTURE_SIZE,pTextureTwo);

    this->block.generateBlock(200, 200, 300, 300, pTextureOne);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                processEvent(event.key.code, true);

                if (up)
                    playerClassROne.move(0.0f,-3.0f);
                if (down)
                    playerClassROne.move(0.0f,3.0f);
                if (right)
                    playerClassROne.move(3.0f,0.0f);
                if (left)
                    playerClassROne.move(-3.0f,0.0f);

            }
            if (event.type == sf::Event::KeyReleased)
            {
                processEvent(event.key.code, false);
            }
        }

        window.clear();
        window.draw(playerClassROne);
        window.draw(playerClassRTwo);
        window.draw(this->block.getBlock());
        window.display();
    }
}

void Game::processEvent(sf::Keyboard::Key key, bool checkPressed) {
    if (checkPressed)
    {
        if (key == sf::Keyboard::W)
            up = true;
        if (key == sf::Keyboard::A)
            left = true;
        if (key == sf::Keyboard::S)
            down = true;
        if (key == sf::Keyboard::D)
            right = true;
    }
    if (!checkPressed)
    {
        up = false;
        down = false;
        right = false;
        left = false;
    }

}

