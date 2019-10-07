#include "Tower.h"
#include <iostream>
#include <math.h>
#include "definitions.h"
#include "iomanip"
#include "sstream"

#define PI 3.14159265

Tower::Tower(sf::Texture &_towerTexture, sf::Texture &_projectileTexture, sf::Texture &_upgTexture, sf::Font &font)
{
    _upgTexture.setSmooth(true);
    this->towerTexture = _towerTexture;
    this->projectileTexture = _projectileTexture;
    this->towerSprite.setTexture(towerTexture);
    this->towerSprite.setScale(0.5,0.5);
    this->upgSprite.setTexture(_upgTexture);
    this->upgSprite.setScale(1.7, 1.7);
    this->upgSprite.setColor(sf::Color::Green);   
    
    this->towerInfo.setFont(font);
    this->towerInfo.setCharacterSize(14);
    this->towerInfo.setPosition(SCREEN_WIDTH-125, SCREEN_HEIGHT-770);
    this->towerInfo.setFillColor(sf::Color::White);
    this->upgradeTimer.resetTimer();
    this->upgradeTimer.resumeTimer();
}
