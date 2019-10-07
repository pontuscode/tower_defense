#include "enemy.h"
#include "Timer.h"
#include <iostream>
#include <cmath>

//tar in fiendetexturen och fonten som används till healthbar
Enemy::Enemy(sf::Texture &texture ,sf::Font &font) 
{
    this->sprite.setTexture(texture);

//här sätts healthbaren     
    this->hpText.setFont(font);   
    hpText.setCharacterSize(12);
    hpText.setFillColor(sf::Color::Black);    
}

