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

    sf::RenderWindow* gWindow;
    Player playerClass;
    Player* newPlayer;
    Block home;
    Block stone;
    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;
    bool space = false;
public:
    Game();
    virtual ~Game();
    void render();
    void processEvent(sf::Keyboard::Key key, bool checkPressed);
    void rmBullets(std::vector<Bullet*> bullets);

    //news
    void runGame();

    void updateEvents();
    void updateControls();
    void updateWindow();
    void updateBullets();
    void renderWindow();
private:
    //news
    void initWindow();
    void initNewPlayer();
    void initTextures();
};
