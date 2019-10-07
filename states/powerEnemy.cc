#include "powerEnemy.h"
#include "Timer.h"
#include <cmath>




powerEnemy::powerEnemy(float const& levelHp, sf::Texture &texture, sf::Font &font) : Enemy{texture, font}
{
    this->health = levelHp*3;
    this->startHealth = levelHp*3;
    this->calculateHp(); //beräknar Hp-baren i procent.
    this->speed = 1.25;

    rect.setPosition(20, 110);
    rect.setSize(sf::Vector2f(45.0f,45.0f));
    rect.setOrigin(24.0f,32.0f);

    sprite.setPosition(rect.getPosition().x -20, rect.getPosition().y -45);
    sprite.setTextureRect(sf::IntRect(0,64,48,64));
    sprite.setScale(0.8f , 0.8f);
    hpText.setPosition(rect.getPosition().x-18, rect.getPosition().y-47);   
    std::vector<int> x_wpts{735,735,160,160,1055,1055,930,930};
    std::vector<int> y_wpts{108,493,493,236,236,493,493,813};
    this->waypoint_y = y_wpts;
    this->waypoint_x = x_wpts;  
}

//spriten sätts där rectangeln är
void powerEnemy::update()
{
    sprite.setPosition(rect.getPosition().x - 20, rect.getPosition().y - 45);
    if(slowedTimer.getTimer() > 2.0f && this->isSlowed)
    {
        this->speed = 1.25;
        this->isSlowed = false;
    }
}

//se zombie.cc
void powerEnemy::moveEnemy()
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
        this->moveDown( animationTimer);
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
        if(rect.getPosition().x >= waypoint_x[waypoint_index] && rect.getPosition().y >= waypoint_y[waypoint_index])
        {
            waypoint_index++;
        }
    }
}

float powerEnemy::getHealth()
{
    return health;
}

//då fiendernas spritesheet har olika dimensioner behöver en hårdkodning av setTextureRect göras
void powerEnemy::moveUp( Timer &animationTimer)
{
    this->sprite.setTextureRect(sf::IntRect(walkingCounter*48,0,48,64));
    if (this->animationTimer.getTimer() >= 0.15f)
    {
        walkingCounter++;
        animationTimer.resetTimer();
    }
    if(walkingCounter > 2)
        walkingCounter=0;
    rect.move(0, -speed);
    this->hpText.move(0, -speed);
}

void powerEnemy::moveDown( Timer &animationTimer)
{
    this->sprite.setTextureRect(sf::IntRect(walkingCounter*48,128,48,64));
    if (this->animationTimer.getTimer() >= 0.15f)
    {
        walkingCounter++;
        animationTimer.resetTimer();
    }
    if(walkingCounter > 2)
        walkingCounter=0;
    rect.move(0, speed);
    this->hpText.move(0, speed);

}
void powerEnemy::moveRight( Timer &animationTimer)
{
    this->sprite.setTextureRect(sf::IntRect(walkingCounter*48,64,48,64));
    if (this->animationTimer.getTimer() >= 0.15f)
    {
        walkingCounter++;
        animationTimer.resetTimer();
    }
    if(walkingCounter > 2)
    {
        walkingCounter=0;
    }
    rect.move(speed, 0);
    this->hpText.move(speed, 0);
}

void powerEnemy::moveLeft( Timer &animationTimer)
{
    this->sprite.setTextureRect(sf::IntRect(walkingCounter*48,192,48,64));
    if (this->animationTimer.getTimer() >= 0.15f)
    {
        walkingCounter++;
        animationTimer.resetTimer();
    }
    if(walkingCounter > 2)
        walkingCounter=0;
    rect.move(-speed, 0);
    this->hpText.move(-speed, 0);
}

bool powerEnemy::isDead() const
{
    return this->health <= 0;
}

void powerEnemy::hitEnemy(float const& dmg, bool slowingShot)
{
    this->health -= dmg; 
    if(slowingShot)
    {
        this->speed = 0.75;
        this->isSlowed = true;
        this->slowedTimer.resetTimer();
    }
}

//beräknar fiendens hp i procent.
void powerEnemy::calculateHp()
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

bool powerEnemy::reachedCastle() const
{
    return waypoint_index >= 8;
}

sf::RectangleShape &powerEnemy::getRectangle()
{
    return rect;
}
sf::Sprite &powerEnemy::getSprite()
{
    return sprite;
}

sf::Text &powerEnemy::getText()
{
    return hpText;
}

sf::Vector2f powerEnemy::getShotPos()
{
    sf::Vector2f temp = this->rect.getPosition();
    if(this->waypoint_index == 0 || this->waypoint_index == 4)
    {
        temp.x += 11.25;
    }
    else if(this->waypoint_index == 1 || this->waypoint_index == 5 || this->waypoint_index == 7)
    {
        temp.y += 11.25;
    }
    else if(this->waypoint_index == 2 || this->waypoint_index == 6)
    {
        temp.x -= 11.25;
    }
    else if(this->waypoint_index == 3)
    {
        temp.y -= 11.25;
    }
    return temp;
}
