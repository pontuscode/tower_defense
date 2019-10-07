#include "castle.h"
#include <iostream>


Castle::Castle()
{
}

int Castle::getCastleHp()
{    
    return this->castleHp;   
}

int Castle::getCoins()
{
    return this->playerCoins;
}

bool Castle::affordTower(int const &towerCost) const
{
    return playerCoins>=towerCost;
}

bool Castle::affordTowerUpgrade(Tower* tower) const
{
    return tower->ableToUpgrade(this->playerCoins);
}

void Castle::decHp(int const& level)
{
//var 10:e level kommer en boss. denne är starkare och skadar slottet med 5 hp.
    if(level % 10 == 0)
    {
        this->castleHp -= 5;
    }
    else 
    {
        this->castleHp -= 1;
    }
}

bool Castle::gameOver() const
{
    return this->castleHp<=0;
}

//multiplier är vilken level du är på. du får 2*level för varje enemy du dödar
void Castle::incCoins(int const &multiplier)
{
    this->playerCoins += multiplier*2;
}

void Castle::decCoins(int const &amount)
{
    this->playerCoins -= amount;
}

void Castle::startGame() //sätter startvärden
{
    this->playerCoins = 225;
    this->castleHp = 10;
}
