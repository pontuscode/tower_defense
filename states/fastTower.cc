#include "fastTower.h"
#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>

#define PI 3.14159265

//beskrivande kommentarer i waterTower.cc och waterTower.h 

fastTower::fastTower(sf::Texture &_towerTexture, sf::Texture &_projectileTexture, sf::Texture &_upgTexture, sf::Font &font) : Tower{_towerTexture,_projectileTexture,_upgTexture, font} 
{
    this->towerSprite.setColor(sf::Color(251, 237, 35));
    this->towerSprite.setOrigin(32.0f, 32.0f);
    this->towerCost = 120;
    this->range = 5;
    this->hitBox.setSize(sf::Vector2f(this->range*64, this->range*64));
    this->hitBox.setOrigin(((this->range*64)/2)-32, ((this->range*64)/2)-32);
    this->hitBox.setFillColor(sf::Color::Transparent);
    this->hitBox.setOutlineColor(sf::Color::White);
    this->hitBox.setOutlineThickness(2.5f);
    this->damage = 1.3f;
    this->fireRate = 0.2;
}

void fastTower::setPositions(sf::Vector2f position)
{
    this->towerSprite.setPosition(position.x + 16.0f, position.y +16.0f);
    this->hitBox.setPosition(position);           
    this->upgSprite.setPosition(position);
}

void fastTower::draw(sf::RenderTarget &target, int const& playerCoins, bool const& displayInfo)
{
    target.draw(towerSprite);
    if(this->ableToUpgrade(playerCoins))
    {
        target.draw(upgSprite);
    }
    if(displayInfo)
    {
        this->updateTowerDetails();
        target.draw(towerInfo);
        target.draw(hitBox);
    }
}

bool fastTower::lookForEnemy(Enemy *enemy) const
{
    if(this->hitBox.getGlobalBounds().intersects(enemy->getRectangle().getGlobalBounds()))
    {
        return true;
    }
    return false;
}

void fastTower::shootEnemy(Enemy *enemy, std::vector <Projectile*> &projectiles)
{
    if(reloadTimer.getTimer() > fireRate)
    {
        sf::Vector2f rectSize = enemy->getRectangle().getSize();
        sf::Vector2f aimHere = enemy->getShotPos();
        float angleX = this->towerSprite.getPosition().x - enemy->getRectangle().getPosition().x+(rectSize.x/2); 
        float angleY = this->towerSprite.getPosition().y - enemy->getRectangle().getPosition().y+(rectSize.y/2);
        float angle = atan(angleY/angleX);
        if(angleX < 0.0f)
        {
            angle -= PI;
        }       
        sf::Vector2f towerPos = this->towerSprite.getPosition();
        enemy->hitEnemy(damage, false);
        projectiles.push_back(new RedLaserProjectile(this->projectileTexture, aimHere, (angle*57.3)+90,towerPos));
        reloadTimer.resetTimer();   
    }
}

bool fastTower::ableToUpgrade(int const& playerCoins)
{
    return playerCoins >= towerCost*2 && this->upgradeTimer.getTimer() > 1.0f;
}

void fastTower::upgrade()
{
    this->upgradeTimer.resetTimer();
    this->damage = damage*2;
    this->towerCost = towerCost*2;
    if(this->upgradeLevel > 3 && this->range < 9)
    {
        this->range += 1;
    }
    this->hitBox.setSize(sf::Vector2f(this->range*64, this->range*64));
    this->hitBox.setOrigin(((this->range*64)/2)-32, ((this->range*64)/2)-32);
    if (this->fireRate > 0.12)
    {
        this->fireRate -= 0.02;
    }
    this->upgradeLevel++;
}

int fastTower::upgradeCost()
{
    return this->towerCost;
}

void fastTower::updateTowerDetails()
{
    std::stringstream strStream;
    strStream << "Fast Tower:\n" << "Level: " << std::to_string(upgradeLevel) << "\nDamage: " << std::fixed << 
        std::setprecision(1) << damage << "\nRange: " << std::fixed << std::setprecision(1) << range << "\nUpg cost: " << 
        std::to_string(towerCost*2) << "\nUpgrades:\n";
    if(this->upgradeLevel > 3 && range < 9)
    {
        strStream << "Damage * 2\n" << "Range+1\n" << "Reload Time -0.02 sec\n";
    }
    else
    {        
        strStream << "Damage * 2\n" << "Reload Time -0.02 sec\n";
    }       
    this->towerInfo.setString(strStream.str());
}

sf::Sprite &fastTower::getTowerSprite()
{
    return towerSprite;
}
sf::Sprite &fastTower::getUpgSprite()
{
    return upgSprite;
}
