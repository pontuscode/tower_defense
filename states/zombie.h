#pragma once

#include <SFML/Graphics.hpp>
#include "enemy.h"
class Zombie : public Enemy
{
public:
    Zombie(float const& level, sf::Texture &texture, sf::Font &font);  
    ~Zombie() = default;

    void update() override;
    void moveEnemy() override;
    float getHealth() override;

    void moveUp(Timer &) override;
    void moveDown(Timer &) override;
    void moveRight(Timer &) override;
    void moveLeft(Timer &) override;

    void hitEnemy(float const& dmg, bool slowingShot) override;
    sf::Vector2f getShotPos() override;
    bool isDead() const override;
    void calculateHp() override;
    bool reachedCastle() const override;

    sf::RectangleShape &getRectangle() override;
    sf::Sprite &getSprite() override;
    sf::Text &getText() override;
};
