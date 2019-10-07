#include "pauseState.h"
#include "definitions.h"
#include <iostream>

/* Finns allmänna kommentarer kring init() och liknande i buildState.cc samt buildState.h */

pauseState::pauseState(gameDataRef initData)
{
    this->data = initData;
}

/*pauseState::~pauseState()
  {}*/

void pauseState::init()
{
    this->data->assets.loadTexture("pauseMenu",
                                   PAUSE_BACKGROUND_FILEPATH);
    this->data->assets.loadTexture("resumeButton",
                                   MENU_RESUME_GAME_BUTTON_FILEPATH);
    this->data->assets.loadTexture("resumeButtonClicked",
                                   MENU_RESUME_GAME_CLICKED_BUTTON_FILEPATH);
    this->data->assets.loadTexture("mainMenuButton",
                                   MENU_RETURN_MAIN_MENU_BUTTON_FILEPATH);
    this->data->assets.loadTexture("mainMenuButtonClicked",
                                   MENU_RETURN_MAIN_MENU_CLICKED_BUTTON_FILEPATH);

    this->pauseMenu.setTexture(this->data->assets.getTexture("pauseMenu"));
    this->resumeButton.setTexture(this->data->assets.getTexture("resumeButton"));
    this->mainMenuButton.setTexture(this->data->assets.getTexture("mainMenuButton"));

    this->pauseMenu.setPosition(
        (SCREEN_WIDTH/2) - (pauseMenu.getGlobalBounds().width/2),
        (SCREEN_HEIGHT/2) - (pauseMenu.getGlobalBounds().height/2));
    this->resumeButton.setPosition(
        (SCREEN_WIDTH/2) - (resumeButton.getGlobalBounds().width/2),
        ((SCREEN_HEIGHT/2) - (resumeButton.getGlobalBounds().height/2)));
    this->mainMenuButton.setPosition(
        (SCREEN_WIDTH/2) - (mainMenuButton.getGlobalBounds().width/2),
        ((SCREEN_HEIGHT/2) - (mainMenuButton.getGlobalBounds().height/2)) + 100);
}

void pauseState::handleInput()
{
    sf::Event event;
    while(this->data->window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            this->data->window.close();
        }
        if(this->data->input.isSpriteClicked(this->resumeButton, sf::Mouse::Left, this->data->window))
        {
            this->resumeButton.setTexture(this->data->assets.getTexture("resumeButtonClicked"));
            while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                this->draw();
            }

            this->resumeButton.setTexture(this->data->assets.getTexture("resumeButton"));   
            this->data->levelTimer.resumeTimer();
            this->data->enemyManager.resumeEnemySpawnTimer();
            this->data->machine.removeState();
        }
        if(this->data->input.isSpriteClicked(this->mainMenuButton, sf::Mouse::Left, this->data->window))
        {
            this->mainMenuButton.setTexture(this->data->assets.getTexture("mainMenuButtonClicked"));

            while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                this->draw();
            }               
            //Om spelaren vill gå tillbaka till Main Menu så måste vektorerna med fiender-, tiles- och projektil-pekare destrueras. Det görs nedan.
            this->data->levelTimer.resetTimer();
            this->data->enemyManager.resumeEnemySpawnTimer();
            this->mainMenuButton.setTexture(this->data->assets.getTexture("mainMenuButton"));
            this->data->machine.removeState();
            this->data->enemyManager.enemyDestructor();
            
            for (auto iter = this->data->projectiles.begin(); iter != this->data->projectiles.end(); )
            {
                delete *iter;
                iter = this->data->projectiles.erase(iter);
            }
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
            this->data->machine.addState(stateRef(new menuState(data)), true);
        }
    }
}

void pauseState::update()
{   
}

void pauseState::draw()
{
    this->data->window.draw(pauseMenu);
    this->data->window.draw(mainMenuButton);
    this->data->window.draw(resumeButton);
    this->data->window.display();
    
}
