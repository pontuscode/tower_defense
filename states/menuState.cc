#include "menuState.h"
#include "gameState.h"
#include "creditState.h"
#include "definitions.h" 
#include <iostream>

menuState::menuState(gameDataRef initData) 
{
    data = initData;
}
 
void menuState::init()
{
    //Laddar in texture i vår map (som har keytype String och valuetype sf::Texture). Stringen är nyckeln för att hämta ut en viss texture. 
    
    //this->data->assets är en datamedlem av typen assetManager i gameData-structen. assetManager sköter om våra fonts, textures, ljud och allt som har med sånt att 
    //göra. Alla klasser som ärver av State har tillgång till gameData-structen, tack vare en shared_ptr<data> som finns i gameLoop.h.

    this->data->assets.loadTexture("background", 
                                   MENU_BACKGROUND_FILEPATH);
    this->data->assets.loadFont("papyrus", PAPYRUS_FONT_FILEPATH);

    //Hämtar ut denna texture och applyar den på vår sprite. getTexture är en funktion i assetManager-klassen som  returnerar en referens till texturen vi laddade in i steget innan. 
    this->background.setTexture(this->data->assets.getTexture("background"));
    this->background.setScale(1.33f, 1.2f);
    //Sätter positionen på våra New game- och Exit Game-knappar. Finns ingen direkt logik i vad SCREEN_WIDTH & SCREEN_HEIGHT sätts till,de har bara fått värden som gjorde att de passade in i den röda bakgrunden på ett bra sätt.

    this->playRect.setPosition(SCREEN_WIDTH - 1250, SCREEN_HEIGHT - 640); 
    this->playRect.setSize(sf::Vector2f(250.0f, 100.0f));
    this->playRect.setFillColor(sf::Color::Transparent);
    this->playRect.setOutlineColor(sf::Color::White);
    this->playRect.setOutlineThickness(1.5f);
    
    this->creditsRect.setPosition(SCREEN_WIDTH - 1250, SCREEN_HEIGHT - 540);
    this->creditsRect.setSize(sf::Vector2f(250.0f, 100.0f));
    this->creditsRect.setFillColor(sf::Color::Transparent);
    this->creditsRect.setOutlineColor(sf::Color::White);
    this->creditsRect.setOutlineThickness(1.5f);

    this->exitRect.setPosition(SCREEN_WIDTH - 1250, SCREEN_HEIGHT - 440);
    this->exitRect.setSize(sf::Vector2f(250.0f, 100.0f));
    this->exitRect.setFillColor(sf::Color::Transparent);
    this->exitRect.setOutlineColor(sf::Color::White);
    this->exitRect.setOutlineThickness(1.5f);

    this->playText.setFont(this->data->assets.getFont("papyrus"));
    this->playText.setFillColor(sf::Color::White);
    this->playText.setCharacterSize(30);
    this->playText.setPosition(playRect.getPosition().x + 60.0f, playRect.getPosition().x + 125.0f);
    this->playText.setString("New game");

    this->creditsText.setFont(this->data->assets.getFont("papyrus"));
    this->creditsText.setFillColor(sf::Color::White);
    this->creditsText.setCharacterSize(30);
    this->creditsText.setPosition(creditsRect.getPosition().x + 75.0f, creditsRect.getPosition().y + 25.0f);
    this->creditsText.setString("Credits");

    this->exitText.setFont(this->data->assets.getFont("papyrus"));
    this->exitText.setFillColor(sf::Color::White);
    this->exitText.setCharacterSize(30);
    this->exitText.setPosition(exitRect.getPosition().x + 60.0f, exitRect.getPosition().y + 25.0f);
    this->exitText.setString("Exit game");

}

void menuState::handleInput()
{
    sf::Event event;
    while(this->data->window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            this->data->window.close();
        }
        //input är en datamedlem i gameData-structen av typen inputManager. inputManager-klassen är den som sköter om all input från användaren till fönstret. 
        //isRectClicked är en bool-funktion som tar tre parametrar: en sf::RectangleShape, en musknapp och en windowreferens. om Rect.contains(mouse) så returneras true.
        if(this->data->input.isRectClicked(this->playRect, sf::Mouse::Left, this->data->window))
        {
            this->playRect.setOutlineColor(sf::Color(169,169,169));
            this->playText.setPosition(playText.getPosition().x + 3.0f, playText.getPosition().y + 3.0f);
            while(sf::Mouse::isButtonPressed(sf::Mouse::Left)) //Den här är tänkt att fungera som en "skip if bit is set" ungefär. 
            {
                this->draw();              
            }
            this->playRect.setOutlineColor(sf::Color::White);
            this->playText.setPosition(playText.getPosition().x - 3.0f, playText.getPosition().y - 3.0f);
            //När användaren släpper musknappen ska playRects outline återgå till oklickad färg.
            
            this->data->levelTimer.resetTimer();
            this->data->levelTimer.resumeTimer();
            this->data->machine.addState(stateRef(new gameState(data)), true);
        }
        if(this->data->input.isRectClicked(this->creditsRect, sf::Mouse::Left, this->data->window))
        {
            this->creditsRect.setOutlineColor(sf::Color(169,169,169));
            this->creditsText.setPosition(creditsText.getPosition().x + 3.0f, creditsText.getPosition().y + 3.0f);
            while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                this->draw();
            }
            this->creditsRect.setOutlineColor(sf::Color::White);
            this->creditsText.setPosition(creditsText.getPosition().x - 3.0f, creditsText.getPosition().y - 3.0f);
            this->data->machine.addState(stateRef(new creditState(data)), true);
        }
        if(this->data->input.isRectClicked(this->exitRect, sf::Mouse::Left, this->data->window))
        {
            this->exitRect.setOutlineColor(sf::Color(169,169,169));
            this->exitText.setPosition(exitText.getPosition().x + 3.0f, exitText.getPosition().y + 3.0f);
            while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                this->draw();
            }     
            this->data->window.close();         
        }
    }
}

void menuState::update()
{
}


void menuState::draw()
{
    this->data->window.clear();
    this->data->window.draw(this->background);
    this->data->window.draw(this->playText);
    this->data->window.draw(this->creditsText);
    this->data->window.draw(this->exitText);

    sf::Vector2i mousePos = sf::Mouse::getPosition(this->data->window);
    if(this->data->input.checkRectMouseover(this->playRect, mousePos))
    {
        this->data->window.draw(playRect);
    }
    if(this->data->input.checkRectMouseover(this->creditsRect, mousePos))
    {
        this->data->window.draw(this->creditsRect);
    }
    if(this->data->input.checkRectMouseover(this->exitRect, mousePos))
    {        
        this->data->window.draw(this->exitRect);
    }
    this->data->window.display();
}
