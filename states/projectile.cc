#include "projectile.h"
#include <cmath>
#include <iostream>

Projectile::Projectile(sf::Texture &texture, sf::Vector2f const& aim, float const& angle, sf::Vector2f const& position)
{
    texture.setSmooth(true);
    this->sprite.setTexture(texture);
    this->sprite.setRotation(angle);
    this->sprite.setPosition(position.x + 16.0f, position.y + 16.0f);
    this->moveHere.x = (position.x - aim.x);
    this->moveHere.y = (position.y - aim.y);
    this->lifeTime = (sqrt(pow(moveHere.x, 2.0) + pow(moveHere.y, 2.0)))/1000; //millisekunder
    this->xSpeed = (aim.x - position.x)*lifeTime;
    this->ySpeed = (aim.y - position.y)*lifeTime;
    std::cout << lifeTime << std::endl;
}

bool Projectile::checkLifecycle() 
{
    return (lifeTimer.getTimer() > lifeTime || lifeTimer.getTimer() > 0.14f);
}

void Projectile::draw(sf::RenderTarget &target) const
{
    target.draw(sprite);   
}


RedLaserProjectile::RedLaserProjectile(sf::Texture &texture, sf::Vector2f const& aimHere, float const& angle, sf::Vector2f const& position) :
    Projectile{texture, aimHere, angle, position}
{
    this->sprite.setTextureRect(sf::IntRect(42,174,9,21));
    this->sprite.setOrigin(4.5f, 0.0f);
}

bool RedLaserProjectile::checkLifecycle()
{
    return (lifeTimer.getTimer() > lifeTime || lifeTimer.getTimer() > 0.14f);
}

void RedLaserProjectile::draw(sf::RenderTarget &target) const
{
    target.draw(sprite);
}

void RedLaserProjectile::moveProjectile() 
{
    this->sprite.move(xSpeed, ySpeed);
}

BlueLaserProjectile::BlueLaserProjectile(sf::Texture &texture, sf::Vector2f const& aimHere, float const& angle, sf::Vector2f const& position) : 
    Projectile{texture, aimHere, angle, position}
{
   this->sprite.setTextureRect(sf::IntRect(209,167,9,21));
   this->sprite.setOrigin(4.5f, 0.0f);
}

bool BlueLaserProjectile::checkLifecycle() 
{
    return (lifeTimer.getTimer() > lifeTime || lifeTimer.getTimer() > 0.14f);
}

void BlueLaserProjectile::draw(sf::RenderTarget &target) const
{
    target.draw(sprite);
}

void BlueLaserProjectile::moveProjectile()
{
    this->sprite.move(xSpeed, ySpeed);
}


GreenLaserProjectile::GreenLaserProjectile(sf::Texture &texture, sf::Vector2f const& aimHere, float const& angle, sf::Vector2f const& position) :
    Projectile{texture, aimHere, angle, position}
{
    this->sprite.setTextureRect(sf::IntRect(44,60,9,21));
    this->sprite.setOrigin(4.5f, 0.0f);
}

bool GreenLaserProjectile::checkLifecycle() 
{
    return (lifeTimer.getTimer() > lifeTime || lifeTimer.getTimer() > 0.14f);
}

void GreenLaserProjectile::draw(sf::RenderTarget &target) const
{
    target.draw(sprite);
}

void GreenLaserProjectile::moveProjectile()
{
    this->sprite.move(xSpeed, ySpeed);
}


IceLaserProjectile::IceLaserProjectile(sf::Texture &texture, sf::Vector2f const& aimHere, float const& angle, sf::Vector2f const& position) :
    Projectile{texture, aimHere, angle, position}
{
    this->sprite.setTextureRect(sf::IntRect(125,170,9,21));
    this->sprite.setOrigin(4.5f, 0.0f);
}

bool IceLaserProjectile::checkLifecycle() 
{
    return (lifeTimer.getTimer() > lifeTime || lifeTimer.getTimer() > 0.14f);
}

void IceLaserProjectile::draw(sf::RenderTarget &target) const
{
    target.draw(sprite);
}

void IceLaserProjectile::moveProjectile()
{
    this->sprite.move(xSpeed, ySpeed);
}
