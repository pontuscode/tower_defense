#include "Tilemap.h"
#include "Tile.h"
#include <iostream>

Tilemap::Tilemap()
{

}

void Tilemap::buildMap(int width, int height, sf::Texture &texture)
{
    this->texture = texture;
    for (int x = 0; x <  width; x++)
    {
        for (int y =0; y < height; y++)
        {
            if((y == 1 && x < 12) || (x == 11 && y<8 && y > 1)
               || (y == 7 && x>2 && x<12) || (x==2 && y<8 && y>2)
               || (y==3 && (x>2 && x<17)) || (x==16 && (y>3 && y <8)) || ((x==16 && x < 13) && y ==7 )
               || ((x >13 && x < 15) && y >7) || (y == 7 && (x<16 && x > 13)) )
            {
                this->tilemap.push_back( new pathTile{ 0, 0, sf::Vector2f(float(x), float(y)), 32.0f, 64.0f,
                            this->texture} );
               
            }
            else if(x>9 && x < 18) 
            {
                this->tilemap.push_back( new grassTile{ 3, 2, sf::Vector2f(float(x), float(y)), 32.0f, 64.0f, 
                            this->texture} );
            }
            else if(x > 13)
            {
                this->tilemap.push_back( new menuTile{ 3, 5, sf::Vector2f(float(x), float(y)), 32.0f, 64.0f,
                            this->texture} );
            }
            else if(x < 8 && y > 8)
            {
                this->tilemap.push_back( new waterTile { 5, 5, sf::Vector2f(float(x), float(y)), 32.0f, 64.0f, 
                            this->texture} );
            }

            else
            {
                this->tilemap.push_back( new sandTile{ 1, 6, sf::Vector2f(float(x), float(y)), 32.0f, 64.0f, 
                            this->texture} );
            }
            std::cout << x << ' ' << y << std::endl;
        }
    }
}
void Tilemap::drawTiles(sf::RenderWindow &window)
{
    for(unsigned int i = 0; i < this->tilemap.size(); i++)
    {
        sf::RenderStates states;
        this->tilemap.at(i) -> draw(window, states);
    }
}

Tile &Tilemap::at(int index)
{
    return tilemap.at(index);
}
