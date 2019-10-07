#include "Tower.h"
#include <iostream>
#include <math.h>
#include "definitions.h"
#include "iomanip"
#include "sstream"
#include "iceTower.h"

#define PI 3.14159265

iceTower::iceTower(sf::Texture &_towerTexture, sf::Texture &_projectileTexture, sf::Texture &_upgTexture, sf::Font &font) : Tower{_towerTexture, _projectileTexture, _upgTexture, font}
{
    this->towerSprite.setColor(sf::Color(200,255,246));
    this->towerSprite.setOrigin(32.0f, 32.0f);
    this->towerCost = 350;
    this->range = 5; //tornets hitbox sätts till en 10x10-kvadrat. 
    this->hitBox.setSize(sf::Vector2f(this->range*64, this->range*64)); //Hitboxen används för att detektera kollision mellan en fiendes rect och tornets rect
    this->hitBox.setOrigin(((this->range*64)/2) - 32, ((this->range*64)/2) - 32);
    this->hitBox.setFillColor(sf::Color::Transparent);
    this->hitBox.setOutlineColor(sf::Color::White);
    this->hitBox.setOutlineThickness(2.5f); //När spelaren har muspekaren över tornet visas utkanten på tornets hitbox så man kan se dess range. 
    this->damage = 2;
    this->fireRate = 1.7f;
}

void iceTower::setPositions(sf::Vector2f position) 
{
    this->towerSprite.setPosition(position.x + 16.0f, position.y + 16.0f);
    this->hitBox.setPosition(position);           
    this->upgSprite.setPosition(position);
}

//Kollar om man har råd att uppgradera tornet samt om spelaren har muspekaren över just detta torn. Har man råd att uppgradera visas en grön pil, har spelaren muspekaren över tornet visas dess damage, range, osv. i textform. Hitboxen ritas även ut. 

void iceTower::draw(sf::RenderTarget &target, int const& playerCoins, bool const& displayInfo)
{
    target.draw(towerSprite);
    if(this->ableToUpgrade(playerCoins))
    {
        target.draw(upgSprite);
    }
    if(displayInfo)
    {
        this->updateTowerDetails();
        target.draw(towerInfo);
        target.draw(hitBox);
    }
}
bool iceTower::lookForEnemy(Enemy *enemy) const
{
    if(this->hitBox.getGlobalBounds().intersects(enemy->getRectangle().getGlobalBounds())) //Om fiendens rect intersectar tornets rect så är en fiende inom range
    {
        return true;
    }
    return false;
}
//Om enemyInRange() returnerat true kommer vi in här. shootEnemy tar in en pekare på vilken fiende som ska skjutas samt referns till vektorn med våra projektiler. 
void iceTower::shootEnemy(Enemy *enemy, std::vector <Projectile*> & projectiles)
{
    if(reloadTimer.getTimer() > fireRate) //Kollar om tornet har "laddat om". 
    {
        sf::Vector2f rectSize = enemy->getRectangle().getSize();
        sf::Vector2f aimHere = enemy->getShotPos();
        float angleX = this->towerSprite.getPosition().x - enemy->getRectangle().getPosition().x+(rectSize.x/2); 
        float angleY = this->towerSprite.getPosition().y - enemy->getRectangle().getPosition().y+(rectSize.y/2);
        float angle = atan(angleY/angleX); //Arctan (mellan motstående och närliggande katet) för att få ut riktningen på hypotenusan. 
        if(angleX < 0.0f) //Om fienden är till höger om tornet måste ett halvt varv på enhetscirkeln subtraheras. 
        {
            angle -= PI;
        }
        //  float scale = sqrt(pow(angleX/24, 2.0) + pow(angleY/24, 2.0)); //Pythagoras sats för att få ut längden på vektorn.        
        sf::Vector2f towerPos = this->towerSprite.getPosition();

        enemy->hitEnemy(damage, true);
        projectiles.push_back(new IceLaserProjectile(this->projectileTexture,aimHere,(angle*57.3)+90,towerPos));
        reloadTimer.resetTimer();
    }  
}

bool iceTower::ableToUpgrade(int const& playerCoins) 
{
    return playerCoins >= towerCost*2 && this->upgradeTimer.getTimer() > 1.0f; //Vi har en upgradeTimer för att man inte ska råka uppgradera tornet en massa gånger i rad. Innan vi hade denna timer räckte det med att nudda vänsterklick på musen för att spenderar alla pengar man hade och uppgradera tornet tills pengarna tog slut. 
}

void iceTower::upgrade()
{
    this->upgradeTimer.resetTimer();
    this->damage = damage*2;
    this->towerCost = towerCost*2;

    if(range < 7)
    {
        this->range += 1;
    }
    this->hitBox.setSize(sf::Vector2f(this->range*64, this->range*64)); //Hitboxen används för att detektera kollision mellan en fiendes rect och tornets rect
    this->hitBox.setOrigin(((this->range*64)/2) - 32, ((this->range*64)/2) - 32);
    if(this->fireRate >  0.7)
    {
        this->fireRate -= 0.2;
    }
    this->upgradeLevel++;
}

int iceTower::upgradeCost()
{
    return this->towerCost;
}

void iceTower::updateTowerDetails()
{
    std::stringstream strStream;
    strStream << "Ice Tower:\n" << "Level: " << upgradeLevel << "\nDamage: " << std::fixed << 
        std::setprecision(1) << damage << "\nRange: " << range << "\nUpg cost: " << 
       towerCost*2 << "\nUpgrades:\n";
    if(range < 7)
    {
        strStream << "Damage * 2\nRange + 1\nReload time -0.2 sec\n";
    }
    else
    {
        strStream << "Damage * 2\nReload time -0.2 sec\n";
    }
    this->towerInfo.setString(strStream.str());
}

sf::Sprite &iceTower::getTowerSprite()
{
    return towerSprite;
}

sf::Sprite &iceTower::getUpgSprite()
{
    return upgSprite;
}
