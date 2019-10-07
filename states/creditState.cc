#include "creditState.h"
#include "menuState.h"

creditState::creditState(gameDataRef initdata)
{
    this->data = initdata;
}

void creditState::init()
{
    this->data->assets.loadTexture("mainMenuButton", MENU_RETURN_MAIN_MENU_BUTTON_FILEPATH);
    this->data->assets.loadTexture("mainMenuButtonClicked", MENU_RETURN_MAIN_MENU_CLICKED_BUTTON_FILEPATH);
    this->data->assets.loadFont("papyrus", PAPYRUS_FONT_FILEPATH);
    this->background.setTexture(this->data->assets.getTexture("background"));
    this->mainMenuButton.setTexture(this->data->assets.getTexture("mainMenuButton"));
    
    this->background.setScale(1.33f, 1.2f);
    this->rekt.setSize(sf::Vector2f(250.0f, 100.0f));
    this->rekt.setFillColor(sf::Color::Transparent);
    this->rekt.setOutlineColor(sf::Color::White);
    this->rekt.setOutlineThickness(1.5); 
    this->rekt.setPosition(SCREEN_WIDTH - 1225, SCREEN_HEIGHT-150);

    this->creditText.setFont(this->data->assets.getFont("papyrus"));
    this->creditText.setCharacterSize(30);
    this->creditText.setPosition((SCREEN_WIDTH -1150) - 24, (SCREEN_HEIGHT - 678));
    this->creditText.setString("Created by: \nMichael Abraham\nMarkus Gustafsson\nPontus Jarnemyr\nJonatan Vilhelmsson");

    this->mainMenuText.setFont(this->data->assets.getFont("papyrus"));
    this->mainMenuText.setCharacterSize(30);
    this->mainMenuText.setPosition(SCREEN_WIDTH - 1175, SCREEN_HEIGHT - 125);
    this->mainMenuText.setString("Main Menu");
    
}

void creditState::handleInput()
{
    sf::Event event;
    
    while(this->data->window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            this->data->window.close();
        }
        
        if(this->data->input.isRectClicked(this->rekt, sf::Mouse::Left, this->data->window))
        {
            this->rekt.setOutlineColor(sf::Color(169,169,169));
            this->mainMenuText.setPosition(mainMenuText.getPosition().x + 3.0f, mainMenuText.getPosition().y + 3.0f);
            while(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                this->draw();
            }
            this->rekt.setOutlineColor(sf::Color::White);
            this->mainMenuText.setPosition(mainMenuText.getPosition().x - 3.0f, mainMenuText.getPosition().y - 3.0f);
            this->data->machine.addState(stateRef(new menuState(data)), true);
        }
    }
}

void creditState::update()
{

}

void creditState::draw()
{
    this->data->window.clear();
    this->data->window.draw(background);
    this->data->window.draw(creditText);
    this->data->window.draw(mainMenuText);
    sf::Vector2i mousePos = sf::Mouse::getPosition(this->data->window);
    if(this->data->input.checkRectMouseover(this->rekt, mousePos))
    {
        this->data->window.draw(rekt);
    }
    this->data->window.display();
}
