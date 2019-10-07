#include "gameOverState.h"

gameOverState::gameOverState(gameDataRef initData)
{
    this->data = initData; //en gameDataRef som tilldelas initdata
}

void gameOverState::init()
{
//laddar in texturer till game-over menyn
    this->data->assets.loadTexture("gameOverMenu", GAME_OVER_MENU_BACKGROUND_FILEPATH);
    this->data->assets.loadTexture("playAgainButton", PLAY_AGAIN_BUTTON_FILEPATH);
    this->data->assets.loadTexture("playAgainButtonClicked", PLAY_AGAIN_BUTTON_CLICKED_FILEPATH);
    this->data->assets.loadTexture("mainMenuButton", 
                                   MENU_RETURN_MAIN_MENU_BUTTON_FILEPATH);
    this->data->assets.loadTexture("mainMenuButtonClicked", 
                                   MENU_RETURN_MAIN_MENU_CLICKED_BUTTON_FILEPATH);


//sätter texturen och dess position
    this->gameOverMenu.setTexture(this->data->assets.getTexture("gameOverMenu"));
    this->playAgainButton.setTexture(this->data->assets.getTexture("playAgainButton"));
    this->mainMenuButton.setTexture(this->data->assets.getTexture("mainMenuButton"));
     
    this->gameOverMenu.setPosition(
        (SCREEN_WIDTH/2) - (gameOverMenu.getGlobalBounds().width/2),
        (SCREEN_HEIGHT/2) - (gameOverMenu.getGlobalBounds().height/2));
    this->playAgainButton.setPosition(
        (SCREEN_WIDTH/2) - (playAgainButton.getGlobalBounds().width/2), 
        (SCREEN_HEIGHT/2) - (playAgainButton.getGlobalBounds().height/2));
     this->mainMenuButton.setPosition(
        (SCREEN_WIDTH/2) - (mainMenuButton.getGlobalBounds().width/2),
        ((SCREEN_HEIGHT/2) - (mainMenuButton.getGlobalBounds().height/2)) + 100);

     //vid gameover destrueras allt och alla variabler nollställs i enemyDestructor.
     this->data->enemyManager.enemyDestructor();
//även tornen, projektilernas  och tilesens pekare destrueras
     for (auto iter = this->data->towers.begin(); iter != this->data->towers.end(); )
     {
         delete *iter;  
         iter = this->data->towers.erase(iter);
     }
     for (auto iter = this->data->tilemap.begin(); iter != this->data->tilemap.end(); )
     {
         delete *iter;  
         iter = this->data->tilemap.erase(iter);
     }
     for (auto iter = this->data->projectiles.begin(); iter != this->data->projectiles.end(); )
     {
         delete *iter;
         iter = this->data->projectiles.erase(iter);
     }
}

void gameOverState::handleInput()
{
 sf::Event event;
    while(this->data->window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            this->data->window.close();
        }
  

        //nu kollar vi vad användaren väljer att göra, nytt game eller avsluta till main menu.
        if(this->data->input.isSpriteClicked(this->playAgainButton, sf::Mouse::Left, this->data->window))
        {
            this->playAgainButton.setTexture(this->data->assets.getTexture("playAgainButtonClicked"));
            while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                this->draw();
            }

//vill man spela igen tar man bort nuvarande state och ett nytt state initieras
            this->playAgainButton.setTexture(this->data->assets.getTexture("playAgainButton"));   
            this->data->levelTimer.resetTimer();
            this->data->levelTimer.resumeTimer();
            this->data->enemyManager.resumeEnemySpawnTimer();

            this->data->machine.removeState();
            this->data->machine.addState(stateRef(new gameState(data)), true); 
        }
        if(this->data->input.isSpriteClicked(this->mainMenuButton, sf::Mouse::Left, this->data->window))
        {
            this->mainMenuButton.setTexture(this->data->assets.getTexture("mainMenuButtonClicked"));

            while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                this->draw();
            }               
            this->mainMenuButton.setTexture(this->data->assets.getTexture("mainMenuButton"));
            this->data->levelTimer.resetTimer();
            this->data->levelTimer.resumeTimer();

            
            this->data->enemyManager.resumeEnemySpawnTimer();
            
            this->data->machine.removeState();     
            this->data->machine.addState(stateRef(new menuState(data)), true);
        }
    }
}

void gameOverState::update()
{
}

void gameOverState::draw()
{
    this->data->window.draw(gameOverMenu);
    this->data->window.draw(playAgainButton);
    this->data->window.draw(mainMenuButton);
    this->data->window.display();
}                      
