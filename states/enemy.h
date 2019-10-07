#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Timer.h"


//pure virtual då en fiende alltid är från någon annan klass, typ zombie.
class Enemy
{
public:
    Enemy(sf::Texture &texture, sf::Font &font); 
    virtual ~Enemy() = default;

    virtual void update() = 0;
    virtual void moveEnemy() = 0;
    virtual float getHealth() = 0;

    virtual void moveUp(Timer &) = 0;
    virtual void moveDown(Timer &) = 0;
    virtual void moveRight(Timer &) = 0;
    virtual void moveLeft(Timer &) = 0;

    virtual bool isDead() const = 0;
    virtual sf::Vector2f getShotPos() = 0;
    virtual void hitEnemy(float const& dmg, bool slowingShot) = 0;
    virtual void calculateHp()= 0;
    virtual bool reachedCastle() const = 0;

    virtual sf::RectangleShape &getRectangle() = 0;
    virtual sf::Sprite &getSprite() = 0;
    virtual sf::Text &getText() = 0;

protected:
    sf::Text hpText;
    sf::Sprite sprite;
    float speed; //fiendens speed
    float health; //hälsan för varje enemy
    float startHealth; //starthälsan används för att beräkna procentuell hp
    int walkingCounter = 0; //vilken texture i animeringen
    Timer animationTimer; //bestämmer hur snabbt fiendens animation går
    Timer slowedTimer;
    bool isSlowed = false;
    int waypoint_index{0}; 
//sätter waypoints för hur fienden ska gå på banan.
    std::vector<int> waypoint_x{};//Bredd
    std::vector<int> waypoint_y{};//Höjd
    sf::RectangleShape rect;
};

