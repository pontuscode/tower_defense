#include "fastEnemy.h"
#include "Timer.h"
#include <cmath>
#include <iostream>


fastEnemy::fastEnemy(float const& levelHp, sf::Texture &texture, sf::Font &font) : Enemy{texture, font}
{
    this->health = levelHp/2;
    this->startHealth = levelHp/2;
    this->calculateHp(); //beräknar Hp-baren i procent.
    this->speed = 4.0;

    rect.setPosition(22, 95);
    rect.setSize(sf::Vector2f(32.0f,32.0f));
    rect.setOrigin(16.0f,16.0f);

    sprite.setPosition(rect.getPosition().x-22, rect.getPosition().y-25);
    sprite.setTextureRect(sf::IntRect(0,32,32,32));
    sprite.setScale(1.5f , 1.5f);
    hpText.setPosition(rect.getPosition().x-22, rect.getPosition().y-35);  
    std::vector<int> x_wpts{734,734,162,162,1054,1054,926,926};
    std::vector<int> y_wpts{95,483,483,223,223,483,483,751};
    this->waypoint_y = y_wpts;
    this->waypoint_x = x_wpts; 
}

//spriten sätts där rectangeln är
void fastEnemy::update()
{
    sprite.setPosition(rect.getPosition().x-22, rect.getPosition().y -25);
    if(slowedTimer.getTimer() > 2.0f && this->isSlowed)
    {
        this->speed = 4.0;
        this->isSlowed = false;
    }
}

//se zombie.cc
void fastEnemy::moveEnemy()
{
    if(waypoint_index ==0)
    {
        this->moveRight(animationTimer);
        
        if(rect.getPosition().x >= waypoint_x[waypoint_index] && rect.getPosition().y >= waypoint_y[waypoint_index])
        {
            waypoint_index++;
        }
    }
    else if(waypoint_index == 1)
    {
        this->moveDown(animationTimer);
        if(rect.getPosition().x >= waypoint_x[waypoint_index] && rect.getPosition().y >= waypoint_y[waypoint_index])
        {
            waypoint_index++;
        }
    }
    else if(waypoint_index == 2)
    {        
        this->moveLeft(animationTimer);
        if(rect.getPosition().x <= waypoint_x[waypoint_index] && rect.getPosition().y >= waypoint_y[waypoint_index])
        {
            waypoint_index++;
        }
    }
    else if(waypoint_index == 3)
    { 
        this->moveUp(animationTimer);

        if(rect.getPosition().x <= waypoint_x[waypoint_index] && rect.getPosition().y <= waypoint_y[waypoint_index])
        {
            waypoint_index++;
        }
    }
    else if(waypoint_index == 4)
    {
        this->moveRight(animationTimer);
        if(rect.getPosition().x >= waypoint_x[waypoint_index] && rect.getPosition().y <= waypoint_y[waypoint_index])
        {
            waypoint_index++;
        }
    }
    else if(waypoint_index == 5)
    {        
        this->moveDown(animationTimer);
        if(rect.getPosition().x >= waypoint_x[waypoint_index] && rect.getPosition().y >= waypoint_y[waypoint_index])
        {
            waypoint_index++;
        }
    }
    else if(waypoint_index == 6)
    {        
        this->moveLeft(animationTimer);
        if(rect.getPosition().x <= waypoint_x[waypoint_index] && rect.getPosition().y >= waypoint_y[waypoint_index])
        {
            waypoint_index++;
        }
    }
    else if(waypoint_index == 7)
    {        
        this->moveDown( animationTimer);
        if(rect.getPosition().x <= waypoint_x[waypoint_index] && rect.getPosition().y >= waypoint_y[waypoint_index])
        {
            waypoint_index++;
        }
    }
}

//då fiendernas spritesheet har olika dimensioner behöver en hårdkodning av setTextureRect göras
void fastEnemy::moveUp( Timer &animationTimer)
{
    this->sprite.setTextureRect(sf::IntRect(walkingCounter*32,64,32,32));
    if (this->animationTimer.getTimer() >= 0.10f)
    {
        walkingCounter++;
        animationTimer.resetTimer();
    }
    if(walkingCounter > 3)
    {
        walkingCounter=0;
    }
    rect.move(0, -speed);
    this->hpText.move(0, -speed);
}
void fastEnemy::moveDown( Timer &animationTimer)
{
    this->sprite.setTextureRect(sf::IntRect(walkingCounter*32,0,32,32));
    if (this->animationTimer.getTimer() >= 0.10f)
    {
        walkingCounter++;
        animationTimer.resetTimer();
    }
    if(walkingCounter > 3)
    {
        walkingCounter=0;
    }
    rect.move(0, speed);
    this->hpText.move(0, speed);
}
void fastEnemy::moveRight( Timer &animationTimer)
{
    this->sprite.setTextureRect(sf::IntRect(walkingCounter*32,32,32,32));
    if (this->animationTimer.getTimer() >= 0.10f)
    {
        walkingCounter++;
        animationTimer.resetTimer();
    }
    if(walkingCounter > 3)
    {
        walkingCounter=0;
    }
    rect.move(speed, 0);
    this->hpText.move(speed, 0);
}

void fastEnemy::moveLeft( Timer &animationTimer)
{
    this->sprite.setTextureRect(sf::IntRect(walkingCounter*32,96,32,32));
    if (this->animationTimer.getTimer() >= 0.10f)
    {
        walkingCounter++;
        animationTimer.resetTimer();
    }
    if(walkingCounter > 3)
    {
        walkingCounter=0;
    }
    rect.move(-speed, 0);
    this->hpText.move(-speed, 0);
}

bool fastEnemy::isDead() const
{
    return this->health <= 0;
}

void fastEnemy::hitEnemy(float const& dmg, bool slowingShot)
{
    this->health -= dmg; 
    if(slowingShot && !(this->isSlowed))
    {
        this->speed = 2.0;
        this->isSlowed = true;
        this->slowedTimer.resetTimer();
    }
}

//beräknar fiendens hp i procent.
void fastEnemy::calculateHp()
{
    int procentHp{};
    procentHp = std::ceil((health*100)/startHealth);
    if (procentHp < 0)
    {
        procentHp = 0;
    }
    else if(procentHp > 100)
    {
        procentHp = 100;
    }
    std::string str{std::to_string(procentHp)};
    str+=" %";
    str.insert(0, 2, ' ');//denna sätter hpboxen lite åt höger.
    hpText.setString(str); 
}

bool fastEnemy::reachedCastle() const
{
    return waypoint_index >= 8;
}

float fastEnemy::getHealth()
{
    return health;
}

sf::RectangleShape &fastEnemy::getRectangle()
{
    return rect;
}

sf::Sprite &fastEnemy::getSprite()
{
    return sprite;
}

sf::Text &fastEnemy::getText()
{
    return hpText;
}

sf::Vector2f fastEnemy::getShotPos()
{
    sf::Vector2f temp = this->rect.getPosition();
    if(this->waypoint_index == 0 || this->waypoint_index == 4)
    {
        temp.x += 30;
    }
    else if(this->waypoint_index == 1 || this->waypoint_index == 5 || this->waypoint_index == 7)
    {
        temp.y += 30;
    }
    else if(this->waypoint_index == 2 || this->waypoint_index == 6)
    {
        temp.x -= 30;
    }
    else if(this->waypoint_index == 3)
    {
        temp.y -= 30;
    }
    return temp;
}
