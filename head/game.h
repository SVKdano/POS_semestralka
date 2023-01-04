//
// Created by Daniel Lieskovský on 3. 1. 2023.
//


#pragma once
#include <SFML/Graphics.hpp>
#include "block.h"
#include "player.h"

class Game {
private:
    Player playerClass;
    Block home;
    Block stone;
    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;
    bool space = false;
public:
    Game();
    void render();
    void processEvent(sf::Keyboard::Key key, bool checkPressed);
    void rmBullets(std::vector<Bullet*> bullets);
private:
    void setTextureOfMovement();
};
