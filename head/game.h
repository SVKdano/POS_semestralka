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

    void updateEvents();
    void updateControls();
    void updateWindow();
    void updateBullets();

private:
    void initWindow();
    void initNewPlayer();
    void initTextures();
    void initBlocks();
};
