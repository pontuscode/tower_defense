#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <vector>

class Tilemap
{
public:
    Tilemap();
    ~Tilemap() {}

    void buildMap(int width, int height, sf::Texture &texture);
    void drawTiles(sf::RenderWindow &window);
    Tile &at(int index);

private:
    sf::Texture texture;
    std::vector<Tile*> tilemap;
};
