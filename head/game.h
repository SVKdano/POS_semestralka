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
    bool up;
    bool down;
    bool right;
    bool left;
    bool space;
public:
    Game();
    void render();
    void processEvent(sf::Keyboard::Key key, bool checkPressed);
    void update();
    void rmBullets(std::vector<Bullet*> bullets);
};
