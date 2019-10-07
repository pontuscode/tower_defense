#pragma once
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "Timer.h"
#include "projectile.h"


class Tower
{
public:
    Tower(sf::Texture &_towerTexture, sf::Texture &_arrowTexture, sf::Texture &_upgTexture, sf::Font &font);
    virtual void setPositions(sf::Vector2f towerPos) = 0;
    virtual ~Tower() = default;

    virtual void draw(sf::RenderTarget &target, int const& playerCoins, bool const& displayInfo) = 0;
    virtual bool lookForEnemy(Enemy *enemy) const = 0;
    virtual void shootEnemy(Enemy *enemy, std::vector <Projectile*> &projectiles) = 0;

    virtual bool ableToUpgrade(int const& playerCoins) = 0;
    virtual int upgradeCost() = 0;
    virtual void upgrade() = 0;
    virtual void updateTowerDetails() = 0;

    virtual sf::Sprite &getTowerSprite() = 0;
    virtual sf::Sprite &getUpgSprite() = 0;

protected:
    sf::Sprite upgSprite;
    sf::Sprite towerSprite;
    sf::Texture towerTexture;
    sf::Texture projectileTexture;
    sf::RectangleShape hitBox;
    sf::Text towerInfo;
    
    int upgradeLevel = 1;
    int towerCost;
    float range;
    float damage;
    Timer reloadTimer;
    float fireRate;
    Timer upgradeTimer;  
};
