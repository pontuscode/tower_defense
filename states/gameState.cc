#include "gameState.h"
#include "menuState.h"
#include "pauseState.h"
#include "buildState.h"
#include <iostream>
#include "definitions.h"
#include "gameOverState.h"
#include "iomanip"
#include "sstream"


/* Finns allmänna kommentarer kring init() och dylikt i buildState.cc och buildState.h */

gameState::gameState(gameDataRef initData)
{
    data = initData;
}

void gameState::init()
{
    this->data->assets.loadTexture("tilemap", TILEMAP_SPRITESHEET_FILEPATH);
    this->data->assets.loadTexture("zombieSprite1", BLOODY_ZOMBIE_SPRITESHEET_FILEPATH);
    this->data->assets.loadTexture("zombieSprite2", ZOMBIE_SPRITESHEET_FILEPATH);
    this->data->assets.loadTexture("zombieSprite3", ROTTEN_ZOMBIE_SPRITESHEET_FILEPATH);
    this->data->assets.loadTexture("zombieSprite4", HEADLESS_ZOMBIE_SPRITESHEET_FILEPATH);
    this->data->assets.loadTexture("minotaurBossSprite", MINOTAUR_BOSS_SPRITESHEET_FILEPATH);
    this->data->assets.loadTexture("fastEnemySprite", FAST_ENEMY_SPRITESHEET_FILEPATH);
    this->data->assets.loadTexture("powerEnemySprite", STRONG_MINOTAUR_SPRITESHEET_FILEPATH);
    this->data->assets.loadTexture("pauseButtonSprite", MENU_PAUSE_BUTTON_FILEPATH);
    this->data->assets.loadTexture("fastTower", FAST_TOWER_FILEPATH);
    this->data->assets.loadTexture("powerTower", POWER_TOWER_FILEPATH);
    this->data->assets.loadTexture("waterTower", WATER_TOWER_FILEPATH);
    this->data->assets.loadTexture("castle", CASTLE_FILEPATH);
    this->data->assets.loadTexture("laser", LASER_FILEPATH);
    this->data->assets.loadTexture("edgyArrow", UPGRADE_ARROW);
    this->data->assets.loadFont("papyrus", PAPYRUS_FONT_FILEPATH);

    this->castle.setTexture(this->data->assets.getTexture("castle"));
    this->backgroundTexture = this->data->assets.getTexture("tilemap");
    this->pauseButton.setTexture(this->data->assets.getTexture("pauseButtonSprite"));
    this->powerTwrInShop.setTexture(this->data->assets.getTexture("powerTower"));
    this->fastTwrInShop.setTexture(this->data->assets.getTexture("fastTower"));
    this->waterTwrInShop.setTexture(this->data->assets.getTexture("waterTower"));
    this->iceTwrInShop.setTexture(this->data->assets.getTexture("fastTower"));
    
    this->castleHealth.setFont(this->data->assets.getFont("papyrus"));
    this->coins.setFont(this->data->assets.getFont("papyrus"));
    this->level.setFont(this->data->assets.getFont("papyrus"));

    this->castleHealth.setCharacterSize(18);
    this->coins.setCharacterSize(18);
    this->level.setCharacterSize(18);
    
    this->castle.setPosition(SCREEN_WIDTH-420, SCREEN_HEIGHT-80);
    this->coins.setPosition(SCREEN_WIDTH-105, SCREEN_HEIGHT-210);
    this->castleHealth.setPosition(SCREEN_WIDTH-110, SCREEN_HEIGHT-32);
    this->level.setPosition(SCREEN_WIDTH-95, SCREEN_HEIGHT-520);
    
    this->pauseButton.setPosition((SCREEN_WIDTH-80),(SCREEN_HEIGHT-565));
    
    this->castle.setScale(0.4f, 0.4f);
    this->powerTwrInShop.setScale(0.5f, 0.5f);
    this->powerTwrInShop.setColor(sf::Color(138, 104, 157));
    this->fastTwrInShop.setColor(sf::Color(251, 237, 35)); 
    this->fastTwrInShop.setScale(0.5f, 0.5f);
    this->waterTwrInShop.setColor(sf::Color::Blue);
    this->waterTwrInShop.setScale(0.5f, 0.5f);
    this->iceTwrInShop.setColor(sf::Color(200,255,246));
    this->iceTwrInShop.setScale(0.5f,0.5f);
   
    this->powerTwrInShop.setPosition((SCREEN_WIDTH-96), (SCREEN_HEIGHT-492));
    this->fastTwrInShop.setPosition((SCREEN_WIDTH-96), (SCREEN_HEIGHT-422));
    this->iceTwrInShop.setPosition((SCREEN_WIDTH-96), (SCREEN_HEIGHT-352));
    this->waterTwrInShop.setPosition((SCREEN_WIDTH-96), (SCREEN_HEIGHT-282));

    this->powerTwrInfo.setString("Power Tower: \nDamage: 6.2 \nRange: 3 \nReload time: 0.9 sec \nCost: 75 \nWhat does the\nscouter say about\nits power level?");
    this->fastTwrInfo.setString("Fast Tower: \nDamage: 1.3 \nRange: 5 \nReload time: 0.2 sec \nCost: 120 \nGotta go fast!");
    this->waterTwrInfo.setString("Water Tower: \nDamage: 100.0 \nRange: 9 \nReload time: 2 sec \nCost: 500\nCan only be built on\nwater because the\nlaser is too stronk.");   
    this->iceTwrInfo.setString("Ice Tower: \nDamage: 2.0 \nRange: 5 \nReload time: 1 sec \nCost: 250 \nWhat killed the\ndinosaurs?\nThe ice age!");
    this->powerTwrInfo.setPosition(SCREEN_WIDTH-125, SCREEN_HEIGHT-750);
    this->fastTwrInfo.setPosition(SCREEN_WIDTH-125, SCREEN_HEIGHT-750);
    this->waterTwrInfo.setPosition(SCREEN_WIDTH-125, SCREEN_HEIGHT-750);
    this->iceTwrInfo.setPosition(SCREEN_WIDTH-125, SCREEN_HEIGHT-750);
    this->powerTwrInfo.setFont(this->data->assets.getFont("papyrus"));
    this->fastTwrInfo.setFont(this->data->assets.getFont("papyrus"));
    this->waterTwrInfo.setFont(this->data->assets.getFont("papyrus"));
    this->iceTwrInfo.setFont(this->data->assets.getFont("papyrus"));
    this->powerTwrInfo.setCharacterSize(14);
    this->fastTwrInfo.setCharacterSize(14);
    this->waterTwrInfo.setCharacterSize(14);
    this->iceTwrInfo.setCharacterSize(14);
        
    this->data->castle.startGame();
    this->data->levelTimer.resumeTimer();

//Här byggs själva kartan upp. Två for-loopar sköter uppbyggnaden av x-led och y-led på kartan. if-satserna ser till att rätt sorts tile kommer ut på rätt plats på banan. 
    for (int x = 0; x <  20; x++)
    {
        for (int y =0; y < 12; y++)
        {
            if((y == 1 && x < 12) || (x == 11 && y<8 && y > 1)
               || (y == 7 && x>2 && x<12) || (x==2 && y<8 && y>2)
               || (y==3 && (x>2 && x<17)) || (x==16 && (y>3 && y <8)) || ((x==16 && x < 13) && y ==7 )
               || ((x >13 && x < 15) && y >7) || (y == 7 && (x<16 && x > 13)) )
            {
                this->data->tilemap.push_back( new pathTile{ 0, 0, sf::Vector2f(float(x), float(y)), 32.0f, 64.0f, this->backgroundTexture} );
               
            }
            else if(x>9 && x < 18) 
            {
                this->data->tilemap.push_back( new grassTile{ 3, 2, sf::Vector2f(float(x), float(y)), 32.0f, 64.0f, this->backgroundTexture} );
            }
            else if(x > 13)
            {
                this->data->tilemap.push_back( new menuTile{ 3, 5, sf::Vector2f(float(x), float(y)), 32.0f, 64.0f, this->backgroundTexture} );
            }
            else if(x < 8 && y > 8)
            {
                this->data->tilemap.push_back( new waterTile { 5, 5, sf::Vector2f(float(x), float(y)), 32.0f, 64.0f, this->backgroundTexture} );
            }

            else
            {
                this->data->tilemap.push_back( new sandTile{ 1, 6, sf::Vector2f(float(x), float(y)), 32.0f, 64.0f, this->backgroundTexture} );
            }
        }
    }
}

void gameState::handleInput()
{
    sf::Event event;
    while(this->data->window.pollEvent(event))
    {        
        if(event.type == sf::Event::Closed)
        {
            this->data->window.close();
        }

        if(this->data->input.isSpriteClicked(this->pauseButton, sf::Mouse::Left, this->data->window))
        {
            this->data->levelTimer.pauseTimer();
            this->data->enemyManager.pauseEnemySpawnTimer();
            this->data->machine.addState(stateRef(new pauseState(data)), false);
        }

        if(this->data->input.isSpriteClicked(this->powerTwrInShop, sf::Mouse::Left, this->data->window))
        {
            if(this->data->castle.affordTower(75))
            {
                this->data->levelTimer.pauseTimer();
                this->data->enemyManager.pauseEnemySpawnTimer();
                this->data->machine.addState(stateRef(new buildState(data)), false);
            }
        } 
        if(this->data->input.isSpriteClicked(this->fastTwrInShop, sf::Mouse::Left, this->data->window))
        {
            if(this->data->castle.affordTower(120))
            {
                this->data->levelTimer.pauseTimer();
                this->data->enemyManager.pauseEnemySpawnTimer();
                this->data->machine.addState(stateRef(new buildState(data)), false);
            }

        }

        if(this->data->input.isSpriteClicked(this->waterTwrInShop, sf::Mouse::Left, this->data->window))
        {
            if(this->data->castle.affordTower(500))
            {
                this->data->levelTimer.pauseTimer();
                this->data->enemyManager.pauseEnemySpawnTimer();
                this->data->machine.addState(stateRef(new buildState(data)), false);
            }
            
        } 
        if(this->data->input.isSpriteClicked(this->iceTwrInShop, sf::Mouse::Left,this->data->window))
        {
            if(this->data->castle.affordTower(250))
            {
                this->data->levelTimer.pauseTimer();
                this->data->enemyManager.pauseEnemySpawnTimer();
                this->data->machine.addState(stateRef(new buildState(data)), false);
            }
        }        
        for(unsigned int i = 0; i < this->data->towers.size(); i++)
        {
            if(this->data->input.isSpriteClicked(this->data->towers.at(i)->getUpgSprite(), sf::Mouse::Left, 
                                                 this->data->window))
            {
                if(this->data->castle.affordTowerUpgrade(this->data->towers.at(i)) && 
                   this->data->towers.at(i)->ableToUpgrade(this->data->castle.getCoins()))
                {
                    this->data->towers.at(i)->upgrade();
                    this->data->castle.decCoins(this->data->towers.at(i)->upgradeCost());
                }
            }
        }
       
    }      
}

void gameState::update()
{
    if(!this->data->castle.gameOver()) //Hela update inleds med att kolla om spelet är över eller inte. 
    {
        this->data->enemyManager.moveEnemies(); //Flyttar fienderna. 
        //har det gått 2.0 sekunder sedan förra leveln avklarades så är det dags att starta nästa level. 
        if(!(this->data->enemyManager.isLevelClear(this->data->levelTimer)) && this->data->levelTimer.getTimer() > 2.0f) 
        {
            if(this->data->enemyManager.getLevel() % 10 == 0) //Var tionde level skall en boss spawna. 
            {
                this->data->enemyManager.newEnemy(this->data->assets.getTexture("minotaurBossSprite"),
                                                  this->data->assets.getFont("papyrus"));
            }
            else
            {
                if(this->data->enemyManager.getRandomEnemy() == 1)
                {
                    this->data->enemyManager.newEnemy(this->data->assets.getTexture(this->data->enemyManager.randomZombieGenerator()),
                                                      this->data->assets.getFont("papyrus"));
                }
                else if(this->data->enemyManager.getRandomEnemy() == 2)
                {
                    this->data->enemyManager.newEnemy(this->data->assets.getTexture("fastEnemySprite"), this->data->assets.getFont("papyrus"));
                }
                else if(this->data->enemyManager.getRandomEnemy() == 3)
                {
                    this->data->enemyManager.newEnemy(this->data->assets.getTexture("powerEnemySprite"), this->data->assets.getFont("papyrus"));
                }
            }
        }
    
        std::pair <int,int> enemyStatus = this->data->enemyManager.checkEnemyStatus();
//Enemystatus returnerar ett pair<int,int> där första inten anger om en fiende nått slottet och den andra anger om en fiende blivit dödad. 
        for(int i = 0; i < enemyStatus.first; i++)
        {
            this->data->castle.decHp(this->data->enemyManager.getLevel());
        }

        for(int i = 0; i < enemyStatus.second; i++)
        {
            if(this->data->enemyManager.getLevel() % 10 == 0)
            {
                this->data->castle.incCoins(this->data->enemyManager.getLevel()*10);
            }
            else if(this->data->enemyManager.getRandomEnemy() == 3)
            {
                this->data->castle.incCoins(this->data->enemyManager.getLevel()*4);
            }
            else
            {
                this->data->castle.incCoins(this->data->enemyManager.getLevel());
            }
        }
        //Här kollar vi om någon fiende är i range för tornen. 
        this->data->enemyManager.checkEnemyInRange(this->data->towers, this->data->projectiles);
    
//Uppdaterar färgen på tornen i shoppen. Har man inte råd med ett visst torn ska det vara rött i shoppen. 
        if((this->data->castle.affordTower(75)))
        {
            this->powerTwrInShop.setColor(sf::Color(138, 104, 157));
        }
        else
        {
            this->powerTwrInShop.setColor(sf::Color::Red);
        }
        if((this->data->castle.affordTower(120)))
        {
            this->fastTwrInShop.setColor(sf::Color(251, 237, 35)); 
        }
        else
        {
            this->fastTwrInShop.setColor(sf::Color::Red);
        }
        if((this->data->castle.affordTower(500)))
        {
            this->waterTwrInShop.setColor(sf::Color::Blue);
        }
        else
        {
            this->waterTwrInShop.setColor(sf::Color::Red);
        }
        if(this->data->castle.affordTower(250))
        {
            this->iceTwrInShop.setColor(sf::Color(200,255,246));
        }
        else
        {
            this->iceTwrInShop.setColor(sf::Color::Red);
        }

        std::string healthStr{"Health: " + std::to_string(this->data->castle.getCastleHp())}; 
        this->castleHealth.setString(healthStr);
        std::string levelStr{"Level: " + std::to_string(this->data->enemyManager.getLevel())};
        this->level.setString(levelStr);
        std::string coinStr{"Coins: " +std::to_string(this->data->castle.getCoins())};
        this->coins.setString(coinStr);

        int count = 0;
        //Kollar till alla projektiler som finns för tillfället. Har de levt för länge är deras lifeCycle true och de destrueras. 
        for (auto iter = this->data->projectiles.begin(); iter != this->data->projectiles.end();)
        {
            this->data->projectiles.at(count)->moveProjectile();
            if(this->data->projectiles.at(count)->checkLifecycle())
            {
                delete *iter;  
                iter = this->data->projectiles.erase(iter);
                count--;
            }
            else
            {
                iter++;
            }
            count++;
        }
    }              
        
    else //if(!gameOver)                else hamnar vi här och vi byter till gameOverState.
    {
        this->data->levelTimer.pauseTimer();
        this->data->machine.addState(stateRef(new gameOverState(data)), true);
    }
}


void gameState::draw()
{
    this->data->window.clear();

    for(unsigned int i = 0; i < this->data->tilemap.size(); i++)
    {
        sf::RenderStates states;
        this->data->tilemap.at(i) -> draw(this->data->window,states);
    }
    this->data->window.draw(pauseButton);
    this->data->window.draw(fastTwrInShop);
    this->data->window.draw(powerTwrInShop);
    this->data->window.draw(waterTwrInShop);
    this->data->window.draw(iceTwrInShop);
    this->data->enemyManager.drawEnemies(this->data->window);
    
//Koden nedan (fram till nästa kommentar) kollar om muspekaren befinner sig över något torn, antingen på kartan eller i shoppen. Om man håller över ett torn ska dess
//info visas och eventuellt dess hitbox också. 
//mouseOver sätts till true om checkSpriteMouseover returnerar true, och skickas in i tornens draw-funktion. 
    sf::Vector2i mousePos = sf::Mouse::getPosition(this->data->window);
    bool mouseOver = false;
    for(unsigned int i = 0; i < this->data->towers.size(); i++)
    {
        if(this->data->input.checkSpriteMouseover(this->data->towers.at(i)->getTowerSprite(), mousePos))
        {
            mouseOver = true;
        }
        this->data->towers.at(i)->draw(this->data->window, this->data->castle.getCoins(), mouseOver);
        mouseOver = false;
    }
    if(this->data->input.checkSpriteMouseover(this->powerTwrInShop, mousePos))
    {
        this->data->window.draw(powerTwrInfo);
    }
    if(this->data->input.checkSpriteMouseover(this->fastTwrInShop, mousePos))
    {
        this->data->window.draw(fastTwrInfo);
    }
    if(this->data->input.checkSpriteMouseover(this->waterTwrInShop, mousePos))
    {
        this->data->window.draw(waterTwrInfo);
    }
    if(this->data->input.checkSpriteMouseover(this->iceTwrInShop, mousePos))
    {
        this->data->window.draw(iceTwrInfo);
    }
//Här nedan ritar vi bara ut text som kan vara intressant för spelaren, tornet samt alla projektiler. 
    this->data->window.draw(this->castleHealth);
    this->data->window.draw(this->level);
    this->data->window.draw(this->coins);
    this->data->window.draw(this->castle);
    for(unsigned int i = 0; i < this->data->projectiles.size(); i++)
    {
        this->data->projectiles.at(i)->draw(this->data->window);
    }
    this->data->window.display();
}
