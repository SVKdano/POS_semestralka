//
// Created by Daniel Lieskovský on 3. 1. 2023.
//

#include "../head/game.h"

#define WINDOW_X  1200
#define WINDOW_Y  800

Game::Game() {
    this->initWindow();
    this->initTextures();
    this->initNewPlayer();
}

Game::~Game() {
    delete this->gWindow;
    delete this->newPlayer;

    for (auto &x : this->textures) {
        delete x.second;
    }

    for (auto *bullet : this->bullets) {
        delete bullet;
    }
}

void Game::runGame() {
    while (this->gWindow->isOpen()) {
        this->updateWindow();
        this->renderWindow();
    }
}

void Game::initWindow() {
    this->gWindow = new sf::RenderWindow(
            sf::VideoMode(WINDOW_X, WINDOW_Y), "Bulanci"
            );

    this->gWindow->setFramerateLimit(60);
    this->gWindow->setVerticalSyncEnabled(false);
}

void Game::initNewPlayer() {
    this->newPlayer = new Player();
}

void Game::initTextures() {
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("../imgs/strela.png");
}

void Game::renderWindow() {
    this->gWindow->clear();
    this->newPlayer->renderPlayer(*this->gWindow);
    for(auto *bullet : this->bullets) {
        bullet->render(this->gWindow);
    }
    this->gWindow->display();
}

void Game::updateEvents() {
    sf::Event e;

    while (this->gWindow->pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            this->gWindow->close();
        }
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
            this->gWindow->close();
        }
    }
}

void Game::updateControls() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->newPlayer->movePlayer(-1.0f, 0.0f);
        this->newPlayer->updateTexture(sf::Keyboard::A);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->newPlayer->movePlayer(0.0f, -1.0f);
        this->newPlayer->updateTexture(sf::Keyboard::W);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->newPlayer->movePlayer(1.0f, 0.0f);
        this->newPlayer->updateTexture(sf::Keyboard::D);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->newPlayer->movePlayer(0.0f, 1.0f);
        this->newPlayer->updateTexture(sf::Keyboard::S);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->newPlayer->canShoot()) {
        this->bullets.push_back(new Bullet(this->textures["BULLET"], this->newPlayer->getPosition().x,
                                           this->newPlayer->getPosition().y, this->newPlayer->getDirBullet().x,
                                           this->newPlayer->getDirBullet().y, 15.f));
    }

}

void Game::updateWindow() {
    this->updateEvents();

    this->updateControls();

    this->newPlayer->updatePlayer();

    this->updateBullets();
}


void Game::updateBullets() {
    unsigned counter = 0;
    for(auto *bullet : this->bullets) {
        bullet->update();
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f) {
            delete this->bullets.at(counter);
            this->bullets.erase(bullets.begin() + counter);
            --counter;

            //TODO: do not forget to delete this cout
            std::cout << this->bullets.size() << "\n";
        }
        ++counter;
    }

}





