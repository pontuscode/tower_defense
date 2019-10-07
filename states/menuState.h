#pragma once
#include <SFML/Graphics.hpp>
#include "state.h"
#include "gameLoop.h"

class menuState : public State
{
public:

    menuState(gameDataRef initData);
    ~menuState() {}

    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;
    

private:
    
    gameDataRef data;
    sf::Sprite background;
    sf::Text playText;
    sf::Text creditsText;
    sf::Text exitText;
    sf::RectangleShape playRect;
    sf::RectangleShape creditsRect;
    sf::RectangleShape exitRect;
};

