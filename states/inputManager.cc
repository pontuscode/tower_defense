#include "inputManager.h"

bool inputManager::isSpriteClicked(sf::Sprite &object, sf::Mouse::Button button,
                                   sf::RenderWindow &window)const
{
    if (sf::Mouse::isButtonPressed(button))
    {
        //Denna rektangel tar ut värdena för var knappen ligger samt hur stor den är. Sedan körs en koll för att se om muspekaren är inom ramarna för rektangeln.
        sf::IntRect ButtonDimensions(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
        
        if (ButtonDimensions.contains(sf::Mouse::getPosition(window)))
        {
            return true;
        }
    }
    return false;
}

bool inputManager::isRectClicked(sf::RectangleShape &object, sf::Mouse::Button button,
                                   sf::RenderWindow &window)const
{
    if (sf::Mouse::isButtonPressed(button))
    {
        //Denna rektangel tar ut värdena för var knappen ligger samt hur stor den är. Sedan körs en koll för att se om muspekaren är inom ramarna för rektangeln.
        sf::IntRect ButtonDimensions(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
        
        if (ButtonDimensions.contains(sf::Mouse::getPosition(window)))
        {
            return true;
        }
    }
    return false;
}

bool inputManager::checkSpriteMouseover(sf::Sprite &object, sf::Vector2i mousePos)const
{
    sf::IntRect objectDimensions(object.getPosition().x, object.getPosition().y, 
                                 object.getGlobalBounds().width, object.getGlobalBounds().height); 
    if(objectDimensions.contains(mousePos))
    {
        return true;
    }
    return false;
}

bool inputManager::checkRectMouseover(sf::RectangleShape &object, sf::Vector2i mousePos)const
{
    sf::IntRect objectDimensions(object.getPosition().x, object.getPosition().y, 
                                 object.getGlobalBounds().width, object.getGlobalBounds().height);    
    if(objectDimensions.contains(mousePos))
    {
        return true;
    }
    return false;
}

sf::Vector2i getMousePosition(sf::RenderWindow &window) 
{
    return sf::Mouse::getPosition(window);
}
