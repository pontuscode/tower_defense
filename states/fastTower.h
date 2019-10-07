#pragma once
#include <SFML/Graphics.hpp>
#include "Tower.h"



//ärver av Tower. beskrivande kommentarer i waterTower.cc och waterTower.h
class fastTower : public Tower
{
public:
    fastTower(sf::Texture &_towerTexture, sf::Texture &_arrowTexture, sf::Texture &_upgTexture, sf::Font &font);
    void setPositions(sf::Vector2f position) override;
    ~fastTower() = default;

    void draw(sf::RenderTarget &target, int const& playerCoins, bool const& displayInfo) override;
    bool lookForEnemy(Enemy *enemy) const override;
    void shootEnemy(Enemy *enemy, std::vector <Projectile*> &projectiles) override;

    bool ableToUpgrade(int const& playerCoins) override;
    void upgrade() override;
    int upgradeCost() override;
    void updateTowerDetails() override;

    sf::Sprite &getTowerSprite() override;
    sf::Sprite &getUpgSprite() override;
};
