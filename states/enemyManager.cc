#include "enemyManager.h"
#include <iostream>
#include <random>

void EnemyManager::newEnemy(sf::Texture &texture, sf::Font &font)
{
//spawnTimer som bestämmer hur ofta fienden spawnar
    if(this->spawnTimer.getTimer() > 1.0f)
    {
//var 10:e level kommer bossen. här kollar vi att alla fiender inte spawnats och att det inte är bossLevel. om vilkoren är uppfyllda fortsätter vi spawna fiender och push_backa dem i en vector.
        if(!allSpawned && levelCount % 10 != 0)
        {
            if(this->randomEnemy == 1) //vanliga zombies skapas
            {
                this->enemyVector.push_back(new Zombie(enemyHealth, texture, font));                
                this->numberOfEnemies++;
                this->spawnTimer.resetTimer();
            }
            else if(this->randomEnemy == 2 ) //fastEnemies skapas
            {
                this->enemyVector.push_back(new fastEnemy(enemyHealth, texture, font));
                this->numberOfEnemies++;
                this->spawnTimer.resetTimer();
            }
            else if(this->randomEnemy == 3) //powerEnemy skapas
            {
                this->enemyVector.push_back(new powerEnemy(enemyHealth, texture, font));
                this->numberOfEnemies++;
                this->spawnTimer.resetTimer();
            }
        }

        //här skickar vi ut bossen. då vi har en boss blir allspawned true efter första.
        else if(!allSpawned && levelCount % 10 == 0 && this->spawnTimer.getTimer() > 3.0f)
        {
            this->enemyVector.push_back(new Minotaur(enemyHealth, texture, font));
            allSpawned = true;
        }
    }
//har vi skickat ut 10 enemies blir allSpawned ture.
    if(this->numberOfEnemies >= this->enemiesToSpawn) 
    {
        this->spawnTimer.resetTimer();
        this->spawnTimer.pauseTimer(); //pausar timern så att fienderna inte springer ut omgående vid nytt level
        this->allSpawned = true;
    }
}

void EnemyManager::moveEnemies() //denna flytar alla fiender
{
    int i = 0;
    for(auto iter = this->enemyVector.begin(); iter != this->enemyVector.end(); iter++)
    {
        this->enemyVector.at(i)->getSprite().setPosition(this->enemyVector.at(i)->getRectangle().getPosition());
        this -> enemyVector.at(i) -> moveEnemy();      
        i++;
    }
}

void EnemyManager::drawEnemies(sf::RenderWindow &window)
{
    int idx = 0;
    for(auto iter = enemyVector.begin(); iter != enemyVector.end(); iter++)
    {       
        this->enemyVector.at(idx)->update();
        window.draw(this->enemyVector.at(idx) -> getSprite());
        this->enemyVector.at(idx)->calculateHp();//beräknar hp i procent.
        window.draw(this->enemyVector.at(idx) -> getText());//ritar ut hp i procent
        idx++;
    }
}

//kollar om fienden är i range för tornen. om de är det så skjuter tornen på fienderna
void EnemyManager::checkEnemyInRange(std::vector <Tower*>const &towers, std::vector <Projectile*> &projectiles)
{
    bool isInRange = false;
    for(unsigned int enemy = 0; enemy < this->enemyVector.size(); enemy++)
    {
        for(unsigned int tower = 0; tower < towers.size(); tower++)
        {
            isInRange = towers.at(tower)->lookForEnemy(this->enemyVector.at(enemy));
            if(isInRange && this->enemyVector.at(enemy)->getHealth() >= 0.0f)
            {
                towers.at(tower)->shootEnemy(this->enemyVector.at(enemy),projectiles);
            }
        }
    }
}

//en funktion med par. första int i paret kollar om fienden nått slottet. andra int i paret kollar om fienden är död. oavsett utgång raderas fienden. enemystatus används sedan för att öka spelarens pengar och sänka slottets hp.
std::pair<int,int> EnemyManager::checkEnemyStatus()
{
    std::pair <int,int> enemyStatus;
  
    for (auto iter = enemyVector.begin(); iter != enemyVector.end(); )
        if( (*iter)->reachedCastle())
        {            
            delete *iter;  
            enemyStatus.first++;
            iter = enemyVector.erase(iter);
        }
        else if((*iter)->isDead())
        {
            delete *iter;  
            enemyStatus.second++;
            iter = enemyVector.erase(iter);
        }
        else
        {
            iter++;
        }
    return enemyStatus;
}

//kollar om man klarat av leveln. detta sker när alla har spawnat samt att fiendevectorn är tom.
bool EnemyManager::isLevelClear(Timer &levelTimer)
{
    if(this->allSpawned && this->enemyVector.empty())
    {
        this->allSpawned = false;
        this->numberOfEnemies = 0;
        levelTimer.resetTimer();
        this->spawnTimer.resumeTimer();
        levelCount += 1;
        enemyHealth += healthInc*levelCount; //för varje level ökas fiendens hp
        this->randomEnemy = this->randomEnemyGenerator();
        if(randomEnemy ==1) //zombies kommer ut
        {
            this->enemiesToSpawn = 10;
        }
        else if(randomEnemy == 2) //snabba gubbar kommer ut
        {
            this->enemiesToSpawn = 8;
        }
        else if(randomEnemy  == 3)//semiboss
        {
            this->enemiesToSpawn = 3;
        }
  
        return true;
    }
    return false;
}
    
void EnemyManager::pauseEnemySpawnTimer()
{    
    spawnTimer.pauseTimer();
}

void EnemyManager::resumeEnemySpawnTimer()
{
    spawnTimer.resumeTimer();
}

void EnemyManager::resetEnemySpawnTimer()
{
    spawnTimer.resetTimer();
}

//destruerar pekarna för enemies. Den resetar även spelet. 
void EnemyManager::enemyDestructor()
{
    for (auto iter = enemyVector.begin(); iter != enemyVector.end(); )
    {
            delete *iter;  
            iter = enemyVector.erase(iter);
    }
    this->levelCount = 1;
    this->enemyHealth = 10;
    this->numberOfEnemies = 0;
    this->levelClear = false;
    this->allSpawned = false;
}

int EnemyManager::getLevel()
{
    return this->levelCount;
}
//slumpar ut vilken zombietexture som skickas ut. det finns 4 olika texturer. returnerar en sträng.

std::string EnemyManager::randomZombieGenerator() const
{

    std::random_device rnd;
    std::uniform_int_distribution<int> dist(1,4);
    std::string zombie{"zombieSprite"};
    return zombie + std::to_string(dist(rnd));

}

int EnemyManager::randomEnemyGenerator() const
{
    std::random_device rnd;
    std::uniform_int_distribution<int> dist(1,3);
    return dist(rnd);
}
