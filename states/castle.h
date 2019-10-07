#pragma once
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "Tower.h"

class Castle
{

public:
    
    Castle();
    ~Castle() = default;
    
    int getCastleHp(); //hämtar in slottets hp
    int getCoins(); //hämtar spelarens coins

    bool affordTower(int const &towerCost) const; //boolfunktion som kolla om man har råd att köpa tornet
    bool affordTowerUpgrade(Tower* tower) const; //boolfunktion som kolla om man har råd att uppgradera tornet.
    void decHp(int const& level);//minskar slottets hp

    bool gameOver() const;
    void incCoins(int const &multiplier);
    void decCoins(int const &amount);
    void startGame();

private:
    
    int castleHp;
    int playerCoins;
};
