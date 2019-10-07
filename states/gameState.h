#pragma once

#include <SFML/Graphics.hpp>
#include "gameLoop.h"
#include "Tile.h"
#include "state.h"
#include <vector>
#include "enemy.h"
#include "enemyManager.h"
#include "Timer.h"
#include "Tower.h"


class gameState : public State
{
public:
    gameState(gameDataRef initData);
    ~gameState() = default;

    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;

private:   
    
    gameDataRef data;
    sf::Texture backgroundTexture;
    sf::Sprite pauseButton;
    sf::Sprite powerTwrInShop;
    sf::Sprite fastTwrInShop;
    sf::Sprite waterTwrInShop;
    sf::Sprite iceTwrInShop;
    sf::Sprite castle;

    sf::Text castleHealth;
    sf::Text coins;
    sf::Text level;
    sf::Text powerTwrInfo;
    sf::Text fastTwrInfo;
    sf::Text waterTwrInfo;
    sf::Text iceTwrInfo;
};

