#pragma once

#include <SFML/Graphics.hpp>
#include "enemy.h"

class powerEnemy : public Enemy
{
public:
   powerEnemy(float const& level, sf::Texture &texture, sf::Font &font);
    ~powerEnemy() = default;

    void update() override;
    void moveEnemy() override;
    float getHealth() override;

    void moveUp(Timer &) override;
    void moveDown(Timer &) override;
    void moveRight(Timer &) override;
    void moveLeft(Timer &) override;
    
    bool isDead() const override;
    sf::Vector2f getShotPos() override;
    void hitEnemy(float const& dmg, bool slowingShot) override;
    void calculateHp() override;
    bool reachedCastle() const override;

    sf::RectangleShape &getRectangle() override;
    sf::Sprite &getSprite() override;
    sf::Text &getText() override;
};
