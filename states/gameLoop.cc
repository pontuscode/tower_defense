#include "gameLoop.h"
#include "menuState.h"
#include <iostream>
gameLoop::gameLoop(int const& screenWidth, int const& screenHeight, std::string const& gameName)
{
    data->window.create(sf::VideoMode(screenWidth, screenHeight), gameName);
    data->machine.addState(stateRef(new menuState(data)));
    this->run();
}

void gameLoop::run()
{
    auto const target { sf::milliseconds (1000.0/60.0) };
    while(this->data->window.isOpen())
    {        
        this->clock.restart();
 
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)
           || sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            // getActiveStates och processStateChanges kan man läsa mer om i stateMachine.cc och stateMachine.h
            this->data->machine.getActiveState()->handleInput();
        }
        this->data->machine.processStateChanges(); 
        this->data->machine.getActiveState()->update();
        this->data->machine.getActiveState()->draw();
        auto wait_time { target - this->clock.getElapsedTime() };
        sf::sleep (wait_time); //sleep för att spelet ska gå lika snabbt oberoende på hur bra dator man har.
    }
}
