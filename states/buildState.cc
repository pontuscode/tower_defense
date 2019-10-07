#include "buildState.h"
#include "Tower.h"
#include "fastTower.h"
#include "powerTower.h"
#include "waterTower.h"
#include "iceTower.h"
#include <iostream>

buildState::buildState(gameDataRef initdata)
{
    data = initdata; //en gameDataRef som tilldelas initdata
}


void buildState::init()
{     

    //hämtar och laddar in texturen i shopen. skalar om texturen och sätter positionen
    this->powerTwrInShop.setTexture(this->data->assets.getTexture("powerTower"));
    this->fastTwrInShop.setTexture(this->data->assets.getTexture("fastTower"));
    this->waterTwrInShop.setTexture(this->data->assets.getTexture("waterTower"));
    this->iceTwrInShop.setTexture(this->data->assets.getTexture("fastTower"));
    this->fastTwrInShop.setScale(0.5f, 0.5f);
    this->powerTwrInShop.setScale(0.5f, 0.5f);
    this->waterTwrInShop.setScale(0.5f, 0.5f);
    this->iceTwrInShop.setScale(0.5f, 0.5f);
    this->powerTwrInShop.setPosition((SCREEN_WIDTH-96), (SCREEN_HEIGHT-492));
    this->fastTwrInShop.setPosition((SCREEN_WIDTH-96), (SCREEN_HEIGHT-422));
    this->iceTwrInShop.setPosition((SCREEN_WIDTH-96), (SCREEN_HEIGHT-352));
    this->waterTwrInShop.setPosition((SCREEN_WIDTH-96), (SCREEN_HEIGHT-282));
    

//hämtar vi in för att kolla om rektangeln contains muspositionen så att vi vet vilket torn som ska flyttas från shopen.
    sf::IntRect powerIntRect(powerTwrInShop.getPosition().x, powerTwrInShop.getPosition().y, 
                              powerTwrInShop.getGlobalBounds().width, powerTwrInShop.getGlobalBounds().height);
    sf::IntRect fastIntRect(fastTwrInShop.getPosition().x, fastTwrInShop.getPosition().y, 
                             fastTwrInShop.getGlobalBounds().width, fastTwrInShop.getGlobalBounds().height);
    sf::IntRect waterIntRect(waterTwrInShop.getPosition().x, waterTwrInShop.getPosition().y, 
                             waterTwrInShop.getGlobalBounds().width, waterTwrInShop.getGlobalBounds().height);
    sf::IntRect iceTwrRect(iceTwrInShop.getPosition().x, iceTwrInShop.getPosition().y, 
                           iceTwrInShop.getGlobalBounds().width, iceTwrInShop.getGlobalBounds().height);
    

//här kollar vi vilket torn som muspekaren är över
    if(powerIntRect.contains(sf::Mouse::getPosition(this->data->window)))
    { 
        this->towerType = 1;
        this->movingTower.setTexture(this->data->assets.getTexture("powerTower"));
        this->hitBox.setSize(sf::Vector2f(64*3, 64*3));
        this->hitBox.setOrigin((192/2)-32,(192/2)-32);
        this->movingTower.setColor(sf::Color(138, 104, 157));
    }
    else if(fastIntRect.contains(sf::Mouse::getPosition(this->data->window)))
    {
        this->towerType = 2;
        this->movingTower.setTexture(this->data->assets.getTexture("fastTower"));
        this->hitBox.setSize(sf::Vector2f(64*5,64*5));
        this->hitBox.setOrigin((320/2)-32,(320/2)-32);
        this->movingTower.setColor(sf::Color(251, 237, 35));
    }
    else if(waterIntRect.contains(sf::Mouse::getPosition(this->data->window)))
    {
        this->towerType = 3;
        this->movingTower.setTexture(this->data->assets.getTexture("waterTower"));
        this->hitBox.setSize(sf::Vector2f(64*9,64*9));
        this->hitBox.setOrigin((576/2)-32,(576/2)-32);
        this->movingTower.setColor(sf::Color::Blue);
    }
    else if(iceTwrRect.contains(sf::Mouse::getPosition(this->data->window)))
    {
        this->towerType = 4;
        this->movingTower.setTexture(this->data->assets.getTexture("fastTower"));
        this->hitBox.setSize(sf::Vector2f(64*5, 64*5));
        this->hitBox.setOrigin(((64*5)/2)-32, ((64*5)/2)-32);
        this->movingTower.setColor(sf::Color(200,255,246));
    }

//sätter slottets textur, och fonter för menytexter.
    this->castle.setTexture(this->data->assets.getTexture("castle"));
    this->castleHealth.setFont(this->data->assets.getFont("papyrus"));
    this->coins.setFont(this->data->assets.getFont("papyrus"));
    this->level.setFont(this->data->assets.getFont("papyrus"));

    this->castleHealth.setCharacterSize(18);
    this->coins.setCharacterSize(18);
    this->level.setCharacterSize(18);
    
    this->castle.setPosition(SCREEN_WIDTH-420, SCREEN_HEIGHT-80);
    this->coins.setPosition(SCREEN_WIDTH - 105, SCREEN_HEIGHT - 210);
    this->castleHealth.setPosition(SCREEN_WIDTH - 110, SCREEN_HEIGHT - 32);
    this->level.setPosition(SCREEN_WIDTH - 95, SCREEN_HEIGHT - 520);


    std::string healthStr{"Health: " + std::to_string(this->data->castle.getCastleHp())}; 
    this->castleHealth.setString(healthStr);
    std::string levelStr{"Level: " + std::to_string(this->data->enemyManager.getLevel())};
    this->level.setString(levelStr);
    std::string coinStr{"Coins: " +std::to_string(this->data->castle.getCoins())};
    this->coins.setString(coinStr);
    
    this->backgroundTexture = this->data->assets.getTexture("tilemap");
    this->castle.setScale(0.4f, 0.4f);
    this->movingTower.setScale(0.5f, 0.5f);


//kollar om vi har råd med ett till torn, om inte blir tornet rött
    int totalCoins{this->data->castle.getCoins()};
    if(totalCoins < 75)
    {
        this->powerTwrInShop.setColor(sf::Color::Red);
    }
    else
    {
        this->powerTwrInShop.setColor(sf::Color(138, 104, 157));
    }
    if(totalCoins < 120)
    {
        this->fastTwrInShop.setColor(sf::Color::Red);
    }
    else
    {
        this->fastTwrInShop.setColor(sf::Color(251, 237, 35));
    }
    if(totalCoins < 500)
    {
        this->waterTwrInShop.setColor(sf::Color::Red);
    }
    else
    {
        this->waterTwrInShop.setColor(sf::Color::Blue);
    }
    if(totalCoins < 250)
    {
        this->iceTwrInShop.setColor(sf::Color::Red);
    }
    else
    {
        this->iceTwrInShop.setColor(sf::Color(200,255,246));
    }

    this->movingTower.setScale(0.5f, 0.5f);  
    this->hitBox.setFillColor(sf::Color::Transparent);
    // this->hitBox.setOutlineColor();
    this->hitBox.setOutlineThickness(2.5f);

//skip if bit is set
    while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
    }
}

void buildState::handleInput()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(this->data->window);
        int correctTile;
        bool isValid = false; //sann när en tile är ledig och av rätt sort
        bool hasBuilt = false;//sann när tornet har byggts och lagts till i vektorn

        for(unsigned int x = 0; x < this->data->tilemap.size(); x++)
        {
//kollar varje tile om den innehåller muspekaren.
            if((this->data->tilemap.at(x)->getCoords().y+64 > mousePos.y) 
               && (this->data->tilemap.at(x)->getCoords().x+64 > mousePos.x))
            {
//kollar om tilen är av rätt typ samt att den inte har ett torn
                if(this->data->tilemap.at(x)->isValidTile(towerType))
                {                  
//sparar indexplatsen som correcTile och sätter isValid till true och avbryter loopen
                    correctTile = x;
                    isValid = true;
                    break;
                }
                else
                {
                    //är den inte valid nollställer vi x så att man kan prova igen
                    x = 0;
                    break;
                }
            }
        }

        //kollar ifall man kan bygga och vilken torntyp det är, torntyper är satta som integers. Om tilen är valid så push_backar vi med rätt torntyp. 
        if(isValid && towerType == 1)
        {
            this->data->towers.push_back(new powerTower(this->data->assets.getTexture("powerTower"), this->data->assets.getTexture("laser"), this->data->assets.getTexture("edgyArrow"), this->data->assets.getFont("papyrus")));
            hasBuilt = true;
        }
        else if(isValid && towerType == 2)
        {
            this->data->towers.push_back(new fastTower(this->data->assets.getTexture("fastTower"), this->data->assets.getTexture("laser"), this->data->assets.getTexture("edgyArrow"), this->data->assets.getFont("papyrus")));
            hasBuilt = true;
        }
        else if(isValid && towerType == 3)
        {
            this->data->towers.push_back(new waterTower(this->data->assets.getTexture("waterTower"), this->data->assets.getTexture("laser"), this->data->assets.getTexture("edgyArrow"),this->data->assets.getFont("papyrus") ));
            hasBuilt = true;
        }
        else if(isValid && towerType == 4)
        {
            this->data->towers.push_back(new iceTower(this->data->assets.getTexture("fastTower"), this->data->assets.getTexture("laser"), this->data->assets.getTexture("edgyArrow"),this->data->assets.getFont("papyrus") ));
            hasBuilt = true;
        }
        //om vi har kommit så här långt och byggt ett torn minskar vi spelarens coins.
        if(hasBuilt)
        {
            if(towerType == 1)
            {
                this->data->castle.decCoins(75);
            }
            else if(towerType == 2)
            { 
                this->data->castle.decCoins(120);
            }
            else if(towerType == 3)
            {
                this->data->castle.decCoins(500);
            }
            else if(towerType == 4)
            {
                this->data->castle.decCoins(250);
            }
//positionerar tornet mitt i tilen. 
            sf::Vector2f towerPos{float(this->data->tilemap.at(correctTile)->getCoords().x), float(this->data->tilemap.at(correctTile)->getCoords().y)};
            int towerPlacement = this->data->towers.size()-1;
            this->data->towers.at(towerPlacement)->setPositions(towerPos);
            this->data->enemyManager.resumeEnemySpawnTimer();
            this->data->levelTimer.resumeTimer();
            this->data->machine.removeState();
        }
    }    
    //denna gör så att vi kan avbryta ett köp genom att högerklicka
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        this->data->enemyManager.resumeEnemySpawnTimer();
        this->data->levelTimer.resumeTimer();
        this->data->machine.removeState();
    }
} 
    
void buildState::update()
{
    this->movingTower.setPosition((sf::Mouse::getPosition(this->data->window).x)-32, (sf::Mouse::getPosition(this->data->window).y)-32);     
    this->hitBox.setPosition(this->movingTower.getPosition());
}
//ritar ut allt
void buildState::draw()
{
    this->data->window.clear();

//ritar ut kartan.
    for(unsigned int i = 0; i < this->data->tilemap.size(); i++)
    {
        sf::RenderStates states;
        this->data->tilemap.at(i) -> draw(this->data->window,states);
    }
    this->data->window.draw(powerTwrInShop);
    this->data->window.draw(fastTwrInShop);
    this->data->window.draw(waterTwrInShop);
    this->data->window.draw(iceTwrInShop);

    for(unsigned int i = 0; i < this->data->towers.size(); i++)
    {
        this->data->towers.at(i)->draw(this->data->window, this->data->castle.getCoins(), false);
    }
    this->data->enemyManager.drawEnemies(this->data->window);
    this->data->window.draw(hitBox);
    this->data->window.draw(movingTower);
    this->data->window.draw(castleHealth);
    this->data->window.draw(coins);
    this->data->window.draw(level);
    this->data->window.draw(this->castle);
    this->data->window.display();
}
