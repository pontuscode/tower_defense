#pragma once
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "zombie.h"
#include "minotaur.h"
#include "fastEnemy.h"
#include "powerEnemy.h"
#include "Tower.h"
#include "Timer.h"
#include "castle.h"
#include <utility>
#include <vector>

//beskrivande kommentarer i cc-filen.

class EnemyManager
{
public:
    EnemyManager(){}
    ~EnemyManager() = default;

    void newEnemy(sf::Texture &texture, sf::Font &font);
    void moveEnemies();
    void drawEnemies(sf::RenderWindow &window);
    void checkEnemyInRange(std::vector <Tower*>const &towers, std::vector <Projectile*> &projectiles);
    std::pair<int,int> checkEnemyStatus();
    bool isLevelClear(Timer &levelTimer);
    void pauseEnemySpawnTimer();
    void resumeEnemySpawnTimer();
    void resetEnemySpawnTimer();
    void enemyDestructor();
    int getLevel();

    std::string randomZombieGenerator() const;
    int randomEnemyGenerator() const;
    int getRandomEnemy() {return randomEnemy;}



private:
    Timer spawnTimer;
    std::vector<Enemy*> enemyVector;
    int levelCount{1};
    float const healthInc{1.3}; //const variabel. exponetiell ökning på fiendens hp
    float enemyHealth = 10;
    int numberOfEnemies;
    int nrOfSpawnedEnemies;
    int enemiesToSpawn{10};
    int randomEnemy{1};
    bool allSpawned = false;
    bool levelClear = false;
};
