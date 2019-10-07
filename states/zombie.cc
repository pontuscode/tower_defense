#include "zombie.h"
#include "enemy.h"
#include "Timer.h"
#include <cmath>
#include <iostream>


Zombie::Zombie(float const& level, sf::Texture &texture, sf::Font &font) : Enemy{texture, font}
{
    this->health = level;
    this->startHealth = level;
    this->calculateHp();
    this->speed = 2;

    rect.setPosition(15, 100);
    rect.setSize(sf::Vector2f(24,32));
    rect.setOrigin(12.0f,16.0f);

    sprite.setPosition(rect.getPosition().x-15, rect.getPosition().y-30);
    sprite.setTextureRect(sf::IntRect(0,32,24,32));
    sprite.setScale(1.5f , 1.5f);
    hpText.setPosition(rect.getPosition().x-14, rect.getPosition().y-35);   
    std::vector<int> x_wpts{733,733,155,155,1051,1051,923,923};
    std::vector<int> y_wpts{100,486,486,222,222,486,486,798};
    this->waypoint_x = x_wpts;
    this->waypoint_y = y_wpts;
}

void Zombie::update()
{
    sprite.setPosition(rect.getPosition().x-15, rect.getPosition().y-30); 

    if(slowedTimer.getTimer() > 2.0f && this->isSlowed)
    {
        this->speed = 2;
        this->isSlowed = false;
    }
}

//waypoint_index är integers som representerar waypoints på kartan. Vi kollar om rektangeln har nått en viss koordinat, då vet vi att det är dags för fienden att 
//svänga. Alltså ++:as waypoint och kallar på rätt underprogram, t ex moveRight, moveLeft osv. 
void Zombie::moveEnemy()
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

float Zombie::getHealth()
{
    return health;
}

//Skillnaden mellan alla moveUp, moveDown osv är vilken sprite i fiendens spritesheet som väljs. Resten av koden är liknande i alla move-program. 
void Zombie::moveUp(Timer &animationTimer)
{
    this->sprite.setTextureRect(sf::IntRect(walkingCounter*24,0,24,32)); //Byter riktning och animation på sprite. På fiendernas spritesheet så byts riktningen på dem i y-led och   animationer byts i x-led. Därför multipliceras walkingCounter med x-leden för att den ska få en animation. 
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

void Zombie::moveDown(Timer &animationTimer)
{
    this->sprite.setTextureRect(sf::IntRect(walkingCounter*24,64,24,32)); //Byter riktning och animation på sprite. 
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

void Zombie::moveRight(Timer &animationTimer)
{
    this->sprite.setTextureRect(sf::IntRect(walkingCounter*24,32,24,32)); //Byter riktning och animation på sprite. 
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

void Zombie::moveLeft(Timer &animationTimer)
{
    this->sprite.setTextureRect(sf::IntRect(walkingCounter*24,96,24,32)); //Byter riktning och animation på sprite. 
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

void Zombie::hitEnemy(float const& dmg, bool slowingShot)
{
    this->health -= dmg;
    if(slowingShot)
    {
        this->speed = 1;
        this->isSlowed = true;
        this->slowedTimer.resetTimer();
    }
}

bool Zombie::isDead() const
{
    return this->health <= 0;
}

void Zombie::calculateHp()
{
    int procentHp{};
    procentHp = std::ceil((health*100)/startHealth); //Får ut fiendens hp i procentenheter, avrundas uppåt.  
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
    str.insert(0, 2, ' '); //Sätter hpboxen lite åt höger.
    hpText.setString(str); 
}

bool Zombie::reachedCastle() const
{
    return waypoint_index >= 8; //Har fienden nått slottets koordinater så sätts waypoint_index till 8. 
}

sf::RectangleShape &Zombie::getRectangle()
{
    return rect;
}

sf::Sprite &Zombie::getSprite() 
{
    return sprite;
}

sf::Text &Zombie::getText() 
{
    return hpText;
}

sf::Vector2f Zombie::getShotPos()
{
    sf::Vector2f temp = this->sprite.getPosition();
    if(this->waypoint_index == 0 || this->waypoint_index == 4)
    {
        temp.x += 15;
    }
    else if(this->waypoint_index == 1 || this->waypoint_index == 5 || this->waypoint_index == 7)
    {
        temp.y += 15;
    }
    else if(this->waypoint_index == 2 || this->waypoint_index == 6)
    {
        temp.x -= 15;
    }
    else if(this->waypoint_index == 3)
    {
        temp.y -= 15;
    }
    return temp;
}
