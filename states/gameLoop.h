#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "stateMachine.h"
#include "assetManager.h"
#include "inputManager.h"
#include "definitions.h"
#include "Timer.h"
#include "Tile.h"
#include "Tower.h"
#include "castle.h"
#include "enemyManager.h"
#include "projectile.h"

/*gameLoop-klassen gör vad den heter, loopar spelet. Det är i denna klassen vi 
  kommer hantera input och logik, rita på skärmen och liknande. */

struct gameData //alla klasser kommer åt denna struct
{
    stateMachine machine;
    sf::RenderWindow window;
    assetManager assets;
    inputManager input;
    Timer levelTimer;
    std::vector <Tile*> tilemap;
    std::vector <Tower*> towers;
    std::vector <Projectile*> projectiles;
    Castle castle;
    EnemyManager enemyManager;
};
    typedef std::shared_ptr<gameData> gameDataRef; //det är denna vi kommer 
//använda när vi vill komma åt gameData.

class gameLoop
{
public:
    gameLoop(int const& screenWidth, int const& screenHeight, std::string const& gameName);
    ~gameLoop() = default;

private:
    sf::Clock clock;
    gameDataRef data = std::make_shared<gameData>(); 

    void run();
};
