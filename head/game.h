//
// Created by Daniel Lieskovský on 3. 1. 2023.
//


#pragma once
#include "block.h"
#include "player.h"
#include <map>

class Game {
private:
    std::map<std::string, sf::Texture*> textures;
    std::vector<Bullet*> bullets;

    sf::RenderWindow* gWindow;
    sf::Texture backroundTexture;
    sf::Sprite mapBackround;

    Player* newPlayer;
    Player* mockedEnemyPlayer;

    Block* home;
    Block* stone1;
    Block* stone2;
    Block* stone3;

public:
    Game();
    virtual ~Game();

    void runGame();
    void renderWindow();
    void renderMap();

    void updateEvents();
    void updateControls();
    void updateWindow();
    void updateBullets();
    void updateCollision();
private:
    void initWindow();
    void initNewPlayer();
    void initTextures();
    void initBlocks();
    void initMap();

    sf::Vector3f getManifold(const sf::FloatRect& overlap, const sf::Vector2f& collisionNormal);
    void resolve(const sf::Vector3f& manifold);
};
