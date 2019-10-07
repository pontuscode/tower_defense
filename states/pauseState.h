#pragma once
#include <SFML/Graphics.hpp>
#include "menuState.h"
#include "gameState.h"
#include "state.h"
#include "gameLoop.h"
#include "Timer.h"

class pauseState : public State
{

public:
    
    pauseState(gameDataRef initData);
    ~pauseState() = default;

    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;

private:

    gameDataRef data;
    sf::Sprite pauseMenu;
    sf::Sprite resumeButton;
    sf::Sprite mainMenuButton;
};
