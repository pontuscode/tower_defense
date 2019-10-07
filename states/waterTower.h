#pragma once
#include <SFML/Graphics.hpp>
#include "Tower.h"


class waterTower : public Tower
{
public:
    waterTower(sf::Texture &_waterTexture, sf::Texture &_projectileTexture, sf::Texture &_upgTexture, sf::Font &font);
    void setPositions(sf::Vector2f position) override;
    ~waterTower() = default;

    void draw(sf::RenderTarget &target, int const& playerCoins, bool const& displayInfo) override;
    bool lookForEnemy(Enemy *enemy) const override;
    void shootEnemy(Enemy *enemy, std::vector<Projectile*> &projectiles) override;

    bool ableToUpgrade(int const& playerCoins) override;
    void upgrade() override;
    int upgradeCost() override;
    void updateTowerDetails() override;

    sf::Sprite &getTowerSprite() override;
    sf::Sprite &getUpgSprite() override;
};
