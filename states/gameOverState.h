#pragma once
#include "SFML/Graphics.hpp"
#include "menuState.h"
#include "gameState.h"
#include "state.h"
#include "gameLoop.h"
#include "Timer.h"
#include "definitions.h"


class gameOverState : public State
{

public:

    gameOverState(gameDataRef initData);
    ~gameOverState() = default;

    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;



private:

    gameDataRef data;
    sf::Sprite gameOverMenu;
    sf::Sprite playAgainButton;
    sf::Sprite mainMenuButton;
};
