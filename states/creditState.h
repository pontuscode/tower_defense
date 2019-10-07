#pragma once
#include "state.h"
#include "gameLoop.h"
#include "inputManager.h"
#include "definitions.h"
#include <SFML/Graphics.hpp>

class creditState : public State
{
public:
    creditState(gameDataRef initdata);
    ~creditState() = default;
    
    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;

private:
    gameDataRef data;
    sf::RectangleShape rekt;
    sf::Sprite background;
    sf::Sprite mainMenuButton;
    sf::Text mainMenuText;
    sf::Text creditText;
};
