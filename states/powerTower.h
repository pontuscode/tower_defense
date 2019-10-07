#pragma once
#include <SFML/Graphics.hpp>
#include "Tower.h"

/* Beskrivande kommentarer finns i waterTower.cc samt waterTower.h */

class powerTower : public Tower
{
public:
    powerTower(sf::Texture &_towerTexture, sf::Texture &_arrowTexture, sf::Texture &_upgTexture, sf::Font &font);
    void setPositions(sf::Vector2f position) override;
    ~powerTower() = default;

    void draw(sf::RenderTarget &target, int const& playerCoins, bool const& displayInfo) override;
    bool lookForEnemy(Enemy *enemy) const override;
    void shootEnemy(Enemy *enemy, std::vector <Projectile*> &projectiles) override;

    bool ableToUpgrade(int const& playerCoins) override;
    int upgradeCost() override;
    void upgrade() override;
    void updateTowerDetails() override;

    sf::Sprite &getTowerSprite() override;
    sf::Sprite &getUpgSprite() override;
};
