#include "powerTower.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>
#define PI 3.14159265

/* Beskrivande kommentarer finns i waterTower.cc samt waterTower.h */ 

powerTower::powerTower(sf::Texture &_towerTexture, sf::Texture &_projectileTexture, sf::Texture &_upgTexture, sf::Font &font) : Tower{_towerTexture,_projectileTexture, _upgTexture, font}
{
    this->towerSprite.setColor(sf::Color(138, 104, 157));
    this->towerSprite.setOrigin(32.0f, 32.0f);
    this->towerCost = 75;
    this->range = 3;    
    this->hitBox.setSize(sf::Vector2f(this->range*64, this->range*64));
    this->hitBox.setOrigin(((this->range*64)/2)-32, ((this->range*64)/2)-32);
    this->hitBox.setFillColor(sf::Color::Transparent);
    this->hitBox.setOutlineColor(sf::Color::White);
    this->hitBox.setOutlineThickness(2.5f);
    this->damage = 6.2f;    
    this->fireRate = 1.0f;
}

void powerTower::setPositions(sf::Vector2f position) 
{
    this->towerSprite.setPosition(position.x + 16.0f, position.y + 16.0f);
    this->hitBox.setPosition(position);           
    this->upgSprite.setPosition(position);
}

void powerTower::draw(sf::RenderTarget &target, int const& playerCoins, bool const& displayInfo)
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

bool powerTower::lookForEnemy(Enemy *enemy) const
{
    if(this->hitBox.getGlobalBounds().intersects(enemy->getRectangle().getGlobalBounds()))
    {
        
        return true;
    }
    return false;
}

void powerTower::shootEnemy(Enemy *enemy, std::vector <Projectile*> &projectiles)
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
        projectiles.push_back(new BlueLaserProjectile(this->projectileTexture, aimHere,(angle*57.3)+90,towerPos));
        reloadTimer.resetTimer();
    }
}

bool powerTower::ableToUpgrade(int const& playerCoins)
{
    return playerCoins >= towerCost*2 && this->upgradeTimer.getTimer() > 1.0f;
}

int powerTower::upgradeCost()
{
    return this->towerCost;
}

void powerTower::upgrade()
{
    this->upgradeTimer.resetTimer();   
    this->damage = damage*2;
    this->towerCost = towerCost*2;
    if(this->upgradeLevel > 3 && range < 6)
    {
        range += 1;
    }
    if(fireRate > 0.5f)
    {
        this->fireRate -= 0.1f;
    }
    this->hitBox.setSize(sf::Vector2f(this->range*64, this->range*64));
    this->hitBox.setOrigin(((this->range*64)/2)-32, ((this->range*64)/2)-32);
    this->upgradeLevel++;
}

void powerTower::updateTowerDetails()
{
    std::stringstream strStream;
    strStream << "Power Tower:\n" << "Level: " << upgradeLevel << "\nDamage: " << std::fixed << 
        std::setprecision(1) << damage << "\nRange: " << range << "\nUpg cost: " << 
        towerCost*2 << "\nUpgrades:\n";
    if(this->upgradeLevel > 3 && range < 6)
    {
        strStream << "Damage * 2\n" << "Range + 1\n" << "Reload Time -0.1 sec\n";
    }
    else if(fireRate < 0.5f)
    {
        strStream << "Damage * 2\n";
    }
    else
    {
        strStream << "Damage * 2\n" << "Reload Time -0.1 sec\n";
    }
    this->towerInfo.setString(strStream.str());
}

sf::Sprite &powerTower::getTowerSprite()
{
    return towerSprite;
}

sf::Sprite &powerTower::getUpgSprite()
{
    return upgSprite;
}
