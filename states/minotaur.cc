#include "minotaur.h"
#include "Timer.h"
#include <cmath>

//Bossen      

Minotaur::Minotaur(float const& levelHp, sf::Texture &texture, sf::Font &font) : Enemy{texture, font}
{
    this->health = levelHp*10;
    this->startHealth = levelHp*10;
    this->calculateHp(); //beräknar Hp-baren i procent.
    this->speed = 1.0;
    rect.setPosition(25, 100);

    rect.setSize(sf::Vector2f(45.0f,55.0f));
    rect.setOrigin(24.0f,32.0f);
    sprite.setPosition(rect.getPosition().x-25, rect.getPosition().y -45);
    sprite.setTextureRect(sf::IntRect(0,64,48,64));
    hpText.setPosition(rect.getPosition().x-20, rect.getPosition().y-45); 
    std::vector<int> x_wpts{737,737,165,165,1055,1055,930,930};
    std::vector<int> y_wpts{100,485,485,228,228,485,485,813};
    this->waypoint_y = y_wpts;
    this->waypoint_x = x_wpts;  
}

//spriten sätts där rectangeln är
void Minotaur::update()
{
    sprite.setPosition(rect.getPosition().x -25, rect.getPosition().y -45);
    if(slowedTimer.getTimer() > 2.0f && this->isSlowed)
    {
        this->speed = 1;
        this->isSlowed = false;
    }
}

//se zombie.cc
void Minotaur::moveEnemy()
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

float Minotaur::getHealth()
{
    return health;
}

//då fiendernas spritesheet har olika dimensioner behöver en hårdkodning av setTextureRect göras
void Minotaur::moveUp( Timer &animationTimer)
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

void Minotaur::moveDown( Timer &animationTimer)
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

void Minotaur::moveRight( Timer &animationTimer)
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

void Minotaur::moveLeft( Timer &animationTimer)
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

bool Minotaur::isDead() const
{
    return this->health <= 0;
}

void Minotaur::hitEnemy(float const& dmg, bool slowingShot)
{
    this->health -= dmg;   
    if(slowingShot)
    {
        this->speed = 0.5;
        this->isSlowed = true;
        this->slowedTimer.resetTimer();
    }
}

//beräknar fiendens hp i procent.
void Minotaur::calculateHp()
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

bool Minotaur::reachedCastle() const
{
    return waypoint_index >= 8;
}

sf::RectangleShape &Minotaur::getRectangle()
{
    return rect;
}

sf::Sprite &Minotaur::getSprite()
{
    return sprite;
}

sf::Text &Minotaur::getText()
{
    return hpText;
}

sf::Vector2f Minotaur::getShotPos()
{   
    sf::Vector2f temp = this->rect.getPosition();
    if(this->waypoint_index == 0 || this->waypoint_index == 4)
    {
        temp.x += 7.5;
    }
    else if(this->waypoint_index == 1 || this->waypoint_index == 5 || this->waypoint_index == 7)
    {
        temp.y += 7.5;
    }
    else if(this->waypoint_index == 2 || this->waypoint_index == 6)
    {
        temp.x -= 7.5;
    }
    else if(this->waypoint_index == 3)
    {
        temp.y -= 7.5;
    }
    return temp;
}
