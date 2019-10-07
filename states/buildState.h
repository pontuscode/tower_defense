#pragma once

#include <SFML/Graphics.hpp>
#include "state.h"
#include "gameLoop.h"
#include "Tile.h"

class buildState : public State
{

public:
    buildState(gameDataRef initdata); //tar in en shared_ptr med en struct som innehåller alla assetmanager, inputmanager...allt som är relevant för alla states.
    ~buildState() = default;

    void init() override; 
    void handleInput() override ;
    void update() override;
    void draw() override;
    
private:
    gameDataRef data;
    sf::Sprite powerTwrInShop;
    sf::Sprite fastTwrInShop;
    sf::Sprite waterTwrInShop;
    sf::Sprite iceTwrInShop;
    sf::Sprite movingTower; //när vi ska placera ett torn visar spriten vart vi är.
    sf::Text castleHealth;
    sf::Text coins;
    sf::Text level;
    sf::Texture backgroundTexture;
    sf::RectangleShape hitBox;
    sf::Sprite castle;

    int towerType;
    
};
