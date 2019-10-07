#pragma once
#include <SFML/Graphics.hpp>
#include "Timer.h"

class Projectile
{
public:


    Projectile(sf::Texture &texture, sf::Vector2f const& aimHere, float const& angle, sf::Vector2f const& position);
   virtual ~Projectile() = default;

    virtual bool checkLifecycle() = 0; //Varje projektil ska "leva" i 100 millisekunder innan den ska destrueras. 
    virtual void draw(sf::RenderTarget &target) const = 0;
    virtual void moveProjectile() = 0;
    
protected:
    Timer lifeTimer;
    float lifeTime;
    sf::Vector2f moveHere;
    float xSpeed;
    float ySpeed;
    sf::Sprite sprite;
};

class RedLaserProjectile : public Projectile
{
public:
    RedLaserProjectile(sf::Texture &texture, sf::Vector2f const& aimHere, float const&angle, sf::Vector2f const&position);
    ~RedLaserProjectile() = default;

    bool checkLifecycle()  override;
    void draw(sf::RenderTarget &target) const override;
    void moveProjectile() override;
};

class BlueLaserProjectile : public Projectile
{
public:
    BlueLaserProjectile(sf::Texture &texture, sf::Vector2f const& aimHere, float const&angle,  sf::Vector2f const& position);
    ~BlueLaserProjectile() = default;

    bool checkLifecycle()  override;
    void draw(sf::RenderTarget &target) const override;
    void moveProjectile() override;
};

class GreenLaserProjectile : public Projectile
{
public:
    GreenLaserProjectile(sf::Texture &texture, sf::Vector2f const& aimHere, float const&angle, sf::Vector2f const&position);
    ~GreenLaserProjectile() = default;
    
    bool checkLifecycle() override;
    void draw(sf::RenderTarget &target) const override;
    void moveProjectile() override;
};

class IceLaserProjectile : public Projectile
{
public:
    IceLaserProjectile(sf::Texture &texture, sf::Vector2f const& aimHere, float const&angle,  sf::Vector2f const& position);
    ~IceLaserProjectile() = default;

    bool checkLifecycle()  override;
    void draw(sf::RenderTarget &target) const override;
    void moveProjectile() override;
};
