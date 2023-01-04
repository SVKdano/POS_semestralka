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
    window.setFramerateLimit(60);

    sf::Texture movementTextures[4];
    movementTextures[0].loadFromFile("../imgs/BlueUp.png");
    movementTextures[1].loadFromFile("../imgs/BlueRight.png");
    movementTextures[2].loadFromFile("../imgs/BlueDown.png");
    movementTextures[3].loadFromFile("../imgs/BlueLeft.png");


    sf::Texture texturePlayer[3];
    texturePlayer[0].loadFromFile("../imgs/RedDown.png");
    texturePlayer[1].loadFromFile("../imgs/home.png");
    texturePlayer[2].loadFromFile("../imgs/stone.png");

    const sf::Texture *pTextureTwo = &texturePlayer[0];
    const sf::Texture *pTextureHome = &texturePlayer[1];
    const sf::Texture *pTextureStone = &texturePlayer[2];

    sf::RectangleShape playerClassRTwo = this->playerClass
            .generatePlayer(WINDOW_X,WINDOW_Y,TEXTURE_SIZE,pTextureTwo);
    this->playerClass
            .generatePlayer(WINDOW_X,WINDOW_Y,TEXTURE_SIZE,movementTextures);

    this->home.generateBlock(200, 200, 300, 300, pTextureHome);
    this->stone.generateBlock(130,130,rand() % (WINDOW_X - 130), rand() % (WINDOW_Y - 130), pTextureStone);

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

                if (up) {
                    this->playerClass.setDirection(0);
                    this->playerClass.move();
                }
                if (down) {
                    this->playerClass.setDirection(2);
                    this->playerClass.move();
                }
                if (right) {
                    this->playerClass.setDirection(1);
                    this->playerClass.move();
                }
                if (left) {
                    this->playerClass.setDirection(3);
                    this->playerClass.move();
                }
                if (space){
                    playerClass.shoot();
                }
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }

            if (event.type == sf::Event::KeyReleased)
            {
                processEvent(event.key.code, false);
            }
        }
        for (auto &bullet : playerClass.getBullets()) {
            bullet->move();
        }
        rmBullets(playerClass.getBullets());
        window.clear();
        window.draw(playerClassRTwo);
        window.draw(playerClass.getPlayer());
        window.draw(this->home.getBlock());
        window.draw(this->stone.getBlock());
        for (auto &bullet : playerClass.getBullets())
        {
            window.draw(bullet->getBullet());
        }
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
        if (key == sf::Keyboard::Space)
            space = true;
    }
    if (!checkPressed)
    {
        up = false;
        down = false;
        right = false;
        left = false;
        space = false;
    }

}

void Game::rmBullets(std::vector<Bullet *> bullets) {
    if (!bullets.empty()) {
        for (unsigned int i = 0; i < bullets.size(); i++) {
            if (abs(bullets[i]->getPositionX()) > 1200) {
                bullets.erase(bullets.begin() + (i++));
            }
            else if (abs(bullets[i]->getPositionY()) > 800) {
                bullets.erase(bullets.begin() + (i++));
            }
        }
    }
}