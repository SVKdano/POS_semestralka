//
// Created by Daniel Lieskovský on 3. 1. 2023.
//

#include "../head/game.h"

#define WINDOW_X  1200
#define WINDOW_Y  800

Game::Game() {
    this->initWindow();
    this->initTextures();
    this->initBlocks();
    this->initNewPlayer();
}

Game::~Game() {
    delete this->gWindow;
    delete this->newPlayer;
    delete this->mockedEnemyPlayer;

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
    this->newPlayer = new Player(true);
    this->mockedEnemyPlayer = new Player(false);
}

void Game::initTextures() {
    this->textures["BULLET"] = new sf::Texture();
    this->textures["BULLET"]->loadFromFile("../imgs/strela.png");
    this->textures["STONE"] = new sf::Texture();
    this->textures["STONE"]->loadFromFile("../imgs/stone.png");
    this->textures["HOME"] = new sf::Texture();
    this->textures["HOME"]->loadFromFile("../imgs/home.png");
}

void Game::initBlocks() {
    this->home = new Block(textures["HOME"], 420, 100);
    this->stone1 = new Block(textures["STONE"], 250, 500);
    this->stone2 = new Block(textures["STONE"], 500, 380);
    this->stone3 = new Block(textures["STONE"], 850, 530);
}

void Game::renderWindow() {
    this->gWindow->clear();
    this->newPlayer->renderPlayer(*this->gWindow);
    this->mockedEnemyPlayer->renderPlayer(*this->gWindow);
    this->home->renderBlock(this->gWindow);
    this->stone1->renderBlock(this->gWindow);
    this->stone2->renderBlock(this->gWindow);
    this->stone3->renderBlock(this->gWindow);
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
        this->bullets.push_back(new Bullet(this->textures["BULLET"], this->newPlayer->getBulletPosition().x,
                                           this->newPlayer->getBulletPosition().y, this->newPlayer->getDirBullet().x,
                                           this->newPlayer->getDirBullet().y, 15.f));
    }
}

void Game::updateCollision() {
    if (this->newPlayer->getBounds().left < 0.f) {
        this->newPlayer->setPosition(0.f, this->newPlayer->getBounds().top);
    } else if (this->newPlayer->getBounds().left + this->newPlayer->getBounds().width >= this->gWindow->getSize().x) {
        this->newPlayer->setPosition(this->gWindow->getSize().x - this->newPlayer->getBounds().width, this->newPlayer->getBounds().top);
    }

    if (this->newPlayer->getBounds().top < 0.f) {
        this->newPlayer->setPosition(this->newPlayer->getBounds().left, 0.f);
    } else if (this->newPlayer->getBounds().top + this->newPlayer->getBounds().height >= this->gWindow->getSize().y) {
        this->newPlayer->setPosition(this->newPlayer->getBounds().left, this->gWindow->getSize().y - this->newPlayer->getBounds().height);
    }
}

void Game::updateWindow() {
    this->updateEvents();

    this->updateControls();

    this->newPlayer->updatePlayer();

    this->updateCollision();

    this->updateBullets();
}


void Game::updateBullets() {
    //TODO: do not forget to delete cout
    unsigned counter = 0;
    for(auto *bullet : this->bullets) {
        bullet->update();
        if (bullet->getBounds().top + bullet->getBounds().height < 0.f) {
            delete this->bullets.at(counter);
            this->bullets.erase(bullets.begin() + counter);
            --counter;
            std::cout << this->bullets.size() << "\n";
        }else if (bullet->getBounds().left + bullet->getBounds().width < 0.f) {
            delete this->bullets.at(counter);
            this->bullets.erase(bullets.begin() + counter);
            --counter;
            std::cout << this->bullets.size() << "\n";
        } else if (bullet->getBounds().left + bullet->getBounds().width > 1200.f) {
            delete this->bullets.at(counter);
            this->bullets.erase(bullets.begin() + counter);
            --counter;
            std::cout << this->bullets.size() << "\n";
        } else if (bullet->getBounds().top + bullet->getBounds().height > 800.f) {
            delete this->bullets.at(counter);
            this->bullets.erase(bullets.begin() + counter);
            --counter;
            std::cout << this->bullets.size() << "\n";
        } else if (bullet->getBounds().intersects(this->mockedEnemyPlayer->getBounds()))
        {
            delete this->bullets.at(counter);
            this->bullets.erase(bullets.begin() + counter);
            --counter;
            std::cout << "Shoot that G" << std::endl;
        } else if ( bullet->getBounds().intersects(this->stone1->getBounds()) ||
                    bullet->getBounds().intersects(this->stone2->getBounds()) ||
                    bullet->getBounds().intersects(this->stone3->getBounds()) ||
                    bullet->getBounds().intersects(this->home->getBounds())
                    )
        {
            delete this->bullets.at(counter);
            this->bullets.erase(bullets.begin() + counter);
            --counter;
        }
        ++counter;
    }

}









