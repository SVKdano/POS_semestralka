//
// Created by Daniel Lieskovský on 3. 1. 2023.
//

#include "../head/game.h"

#define WINDOW_X  1200
#define WINDOW_Y  800

Game::Game() {
    this->initConnection();
    this->initWindow();
    this->initMap();
    this->initTextures();
    this->initBlocks();
    this->initNewPlayer();
}

Game::~Game() {
    delete this->gWindow;
    delete this->newPlayer;
    delete this->enemyPlayer;

    delete this->home;
    delete this->stone1;
    delete this->stone2;
    delete this->stone3;

    for (auto &x : this->textures) {
        delete x.second;
    }

    for (auto *bullet : this->bullets) {
        delete bullet;
    }

    for (auto *bullet : this->bulletsEnemy) {
        delete bullet;
    }
}

void Game::runGame() {
    while (this->gWindow->isOpen()) {
        this->updateWindow();
        //this->renderWindow();
    }
}

const bool Game::isWindowOpened() {
    return this->gWindow->isOpen();
}

sf::RenderWindow *Game::getWindow() const {
    return  this->gWindow;
}

void Game::initWindow() {
    this->gWindow = new sf::RenderWindow(
            sf::VideoMode(WINDOW_X, WINDOW_Y), "Bulanci"
            );

    this->gWindow->setFramerateLimit(60);
    this->gWindow->setVerticalSyncEnabled(false);
}

void Game::initNewPlayer() {
    if (this->connection == 1) {
        this->newPlayer = new Player(true);
        this->enemyPlayer = new Player(false);
    } else {
        this->newPlayer = new Player(false);
        this->enemyPlayer = new Player(true);
    }
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
    this->stone1 = new Block(textures["STONE"], 210, 300);
    this->stone2 = new Block(textures["STONE"], 500, 640);
    this->stone3 = new Block(textures["STONE"], 920, 350);
}

void Game::initMap() {
    this->backroundTexture.loadFromFile("../imgs/mapa.png");
    this->mapBackround.setTexture(this->backroundTexture);
}

void Game::initConnection() {
    std::cout << "som tu connection" << std::endl;
    std::string local = this->localIP.toString();
    std::cout << local << std::endl;
    std::cin >> this->connection;

    if (this->connection == 1) {
        sf::TcpListener listener;
        listener.listen(5000);
        listener.accept(this->socket);
    } else {
        sf::IpAddress iP;
        std::cout << "Write server IP address." << std::endl;
        std::cin >> iP;
        if(!socket.connect(iP,5000)) {
            std::cout << "Connection successful." << std::endl;
        } else {
            std::cout << "Failed to connect." << std::endl;
        }
    }
}


void Game::renderMap() {
    this->gWindow->draw(this->mapBackround);
}

void Game::renderWindow() {
    this->gWindow->clear();
    this->renderMap();
    this->newPlayer->renderPlayer(*this->gWindow);
    this->enemyPlayer->renderPlayer(*this->gWindow);
    this->enemyPlayer->updateTexture();
    this->home->renderBlock(this->gWindow);
    this->stone1->renderBlock(this->gWindow);
    this->stone2->renderBlock(this->gWindow);
    this->stone3->renderBlock(this->gWindow);
    for(auto *bullet : this->bullets) {
        bullet->render(this->gWindow);
    }
    for(auto *eBullet : this->bulletsEnemy) {
        eBullet->render(this->gWindow);
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
        this->newPlayer->setDirection(3);
        this->newPlayer->updateTexture();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->newPlayer->movePlayer(0.0f, -1.0f);
        this->newPlayer->setDirection(0);
        this->newPlayer->updateTexture();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->newPlayer->movePlayer(1.0f, 0.0f);
        this->newPlayer->setDirection(1);
        this->newPlayer->updateTexture();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->newPlayer->movePlayer(0.0f, 1.0f);
        this->newPlayer->setDirection(2);
        this->newPlayer->updateTexture();
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

    sf::FloatRect overlap;
    sf::FloatRect playerBounds = this->newPlayer->getBounds();

    if (stone1->getBounds().intersects(playerBounds, overlap)) {
        auto collisionNormal = stone1->getPosition() - this->newPlayer->getPosition();
        auto manifold = getManifold(overlap, collisionNormal);
        this->resolve(manifold);
    } else if (stone2->getBounds().intersects(playerBounds, overlap)) {
        auto collisionNormal = stone2->getPosition() - this->newPlayer->getPosition();
        auto manifold = getManifold(overlap, collisionNormal);
        this->resolve(manifold);
    } else if (stone3->getBounds().intersects(playerBounds, overlap)) {
        auto collisionNormal = stone3->getPosition() - this->newPlayer->getPosition();
        auto manifold = getManifold(overlap, collisionNormal);
        this->resolve(manifold);
    } else if (home->getBounds().intersects(playerBounds, overlap)) {
        auto collisionNormal = home->getPosition() - this->newPlayer->getPosition();
        auto manifold = getManifold(overlap, collisionNormal);
        this->resolve(manifold);
    }
}


void Game::updateHit() {
    sf::Packet packerRespawn;
    int respawned = 0;
    sf::Vector2f position;
    unsigned counter = 0;
    for (auto *bullet : this->bulletsEnemy) {
        if (bullet->getBounds().intersects(this->newPlayer->getBounds())) {

            respawned = 1;

            int acutalLives = this->newPlayer->getLives();
            this->newPlayer->setLives(acutalLives - 1);

            if (this->newPlayer->getLives() > 0 ) {
                this->enemyPlayer->respawn();
                this->newPlayer->respawn();
            } else {
                this->enemyPlayer->respawn();
                this->enemyPlayer->setSpeedOfMovement(0);
                this->newPlayer->respawn();
                this->newPlayer->setSpeedOfMovement(0);
            }
        }
    }
    packerRespawn << respawned << this->enemyPlayer->getPosition().x << this->enemyPlayer->getPosition().y<< this->newPlayer->getLives();
    this->socket.send(packerRespawn);

    this->socket.receive(packerRespawn);

    int unpackedRespawn = 0;
    int enemyLives = 0;
    packerRespawn >> unpackedRespawn;
    if (unpackedRespawn == 1) {
        packerRespawn >> position.x;
        packerRespawn >> position.y;
        packerRespawn >> enemyLives;
        this->newPlayer->setPosition(position);
        this->enemyPlayer->setLives(enemyLives);
    }
}

void Game::updateWindow() {

    if (this->firstTimeRender) {
        sf::Packet positionPacked;
        sf::Vector2f positions;
        firstTimeRender = false;
        positionPacked << this->enemyPlayer->getPosition().x << this->enemyPlayer->getPosition().y;
        this->socket.send(positionPacked);

        this->socket.receive(positionPacked);
        positionPacked >> positions.x >> positions.y;

        this->newPlayer->setPosition(positions);
    }

    this->updateEvents();

    if (this->newPlayer->getLives() > 0 && this->enemyPlayer->getLives() > 0) {
        sf::Vector2f prevPos, enemyPos;
        int  prevLife1, prevLife2, life1, life2, enemyDir;

        sf::Packet packetMovement;
        prevPos = this->newPlayer->getPosition();

        this->updateControls();

        this->newPlayer->updatePlayer();

        this->updateCollision();

        this->updateBullets();

        this->updateHit();

        if (this->newPlayer->getPosition() != prevPos) {
            packetMovement << this->newPlayer->getPosition().x << this->newPlayer->getPosition().y
                           << this->newPlayer->getDirection();

        }
        this->socket.send(packetMovement);
        this->socket.receive(packetMovement);

        if (packetMovement >> enemyPos.x >> enemyPos.y >> enemyDir) {
            if (this->enemyPlayer->getDirection() != enemyDir) {
                this->enemyPlayer->setDirection(enemyDir);
            }
            this->enemyPlayer->setPosition(enemyPos);
        }

        int size = this->bullets.size();
        sf::Packet packetSize;
        packetSize << size;

        this->socket.send(packetSize);
        this->socket.receive(packetSize);

        sf::Packet packetBulletX;
        sf::Packet packetBulletY;

        float posX;
        float posY;

        for (auto *bullet : this->bullets) {
            packetBulletX << bullet->getPosition().x;
            packetBulletY << bullet->getPosition().y;
        }

        this->socket.send(packetBulletX);
        this->socket.receive(packetBulletX);
        this->socket.send(packetBulletY);
        this->socket.receive(packetBulletY);

        this->clearEnemyBullets();
        if (packetSize >> size) {
            for (int i = 0; i < size; i++) {
                packetBulletX >> posX;
                packetBulletY >> posY;
                this->bulletsEnemy.push_back(new Bullet(this->textures["BULLET"], posX, posY, 0, 0, 15.f));
            }
        }
    }

}


void Game::updateBullets() {
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
        }  else if ( bullet->getBounds().intersects(this->stone1->getBounds()) ||
                    bullet->getBounds().intersects(this->stone2->getBounds()) ||
                    bullet->getBounds().intersects(this->stone3->getBounds()) ||
                    bullet->getBounds().intersects(this->home->getBounds())
                    ) {
            delete this->bullets.at(counter);
            this->bullets.erase(bullets.begin() + counter);
            --counter;
            std::cout << this->bullets.size() << std::endl;
        }
        ++counter;
    }

}

sf::Vector3f Game::getManifold(const sf::FloatRect &overlap, const sf::Vector2f &collisionNormal) {
    sf::Vector3f manifold;

    if (overlap.width < overlap.height) {
        manifold.x = (collisionNormal.x < 0) ? 1.f : -1.f;
        manifold.z = overlap.width;
    }
    else {
        manifold.y = (collisionNormal.y < 0) ? 1.f : -1.f;
        manifold.z = overlap.height;
    }

    return manifold;
}

void Game::resolve(const sf::Vector3f &manifold) {
    sf::Vector2f normal(manifold.x, manifold.y);
    this->newPlayer->setPosition(this->newPlayer->getPosition() + (normal * manifold.z));
}

void Game::clearEnemyBullets() {
    if (this->bulletsEnemy.size() > 0) {
        for (auto *bullet : this->bulletsEnemy) {
            delete this->bulletsEnemy.at(0);
            this->bulletsEnemy.erase(bulletsEnemy.begin());
        }
    }
}

