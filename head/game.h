//
// Created by Daniel Lieskovský on 3. 1. 2023.
//
#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"

class Game {
    private:
        Player playerClass;
    public:
        Game();
        void render();
};
