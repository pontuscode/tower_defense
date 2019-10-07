#pragma once
#include <SFML/Graphics.hpp> 

/*inputManager kommer vara motorn som sköter all input från användaren. Vi kan 
  mha denna hitta muspositionen, avgöra om vi klickat på en Sprite eller liknande.*/

class inputManager
{
public:
    inputManager() {}
    ~inputManager() = default;

    bool isSpriteClicked(sf::Sprite &object, sf::Mouse::Button button,
                         sf::RenderWindow &window)const;
    bool isRectClicked(sf::RectangleShape &object, sf::Mouse::Button button, sf::RenderWindow &window)const;
    bool checkSpriteMouseover(sf::Sprite &object, sf::Vector2i mousePos)const;
    bool checkRectMouseover(sf::RectangleShape &object, sf::Vector2i mousePos)const;

    sf::Vector2i getMousePosition(sf::RenderWindow &window);
};

