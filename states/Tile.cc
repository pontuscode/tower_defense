#include "Tile.h"


Tile::Tile() {}

//x och y är vilken sprite den ska "välja" i spritesheeten. position är var den ska ligga på kartan. textureDim anger måtten på texturen i spritesheeten. 
//worldDim anger hur stor den ska vara i spelet. texture är hela spritesheetet för våra tiles. 
Tile::Tile(int const& x, int const& y, sf::Vector2f const& position, float const& textureDim, float const& worldDim, sf::Texture texture)

{
    //Här får tileDimensions sin form (Quads) samt sina mått. 
    tileDimensions = sf::VertexArray(sf::PrimitiveType::Quads, 4);
    tileDimensions.append(sf::Vertex((sf::Vector2f(0.0f, 0.0f) + position) * worldDim, 
                                 sf::Vector2f(textureDim * x, textureDim * y)));

    tileDimensions.append(sf::Vertex((sf::Vector2f(1.0f, 0.0f) + position) * worldDim, 
                                 sf::Vector2f(textureDim * x + textureDim, textureDim * y)));

    tileDimensions.append(sf::Vertex((sf::Vector2f(1.0f, 1.0f) + position) * worldDim, 
                                 sf::Vector2f(textureDim * x + textureDim, textureDim * y + textureDim)));

    tileDimensions.append(sf::Vertex((sf::Vector2f(0.0f, 1.0f) + position) * worldDim, 
                                 sf::Vector2f(textureDim * x, textureDim * y + textureDim))); 

    this->tileTexture = texture;
    this->xCoord = (int)(position.x)*64;
    this->yCoord = (int)(position.y)*64;
    this->hasTower = false; 
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &tileTexture;
    target.draw(tileDimensions, states);
}



sandTile::sandTile(int const& x, int const&y, sf::Vector2f const&position, float const&textureDim, float const&worldDim, sf::Texture texture) : Tile(x,y,position,textureDim,worldDim,texture)
{
}

void sandTile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Tile::draw(target,states);
}

sf::Vector2i sandTile::getCoords() const
{
    sf::Vector2i tempVektor;
    tempVektor.x = this->xCoord;
    tempVektor.y = this->yCoord;
    return tempVektor;
}

bool sandTile::isValidTile(int const& towerType)
{
    if(!hasTower && towerType != 3) //towerType 3 är ett waterTower. Ska ej gå att bygga på någon annan tile än waterTile. 
    {
        hasTower = true;
        return true;
    }
    else
    {
        return false;
    }
}



grassTile::grassTile(int const&x, int const&y, sf::Vector2f const&position, float const&textureDim, float const&worldDim, sf::Texture texture) : Tile(x,y,position,textureDim,worldDim,texture)
{						       
}

void grassTile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Tile::draw(target,states);
}

sf::Vector2i grassTile::getCoords() const 
{
    sf::Vector2i tempVektor;
    tempVektor.x = this->xCoord;
    tempVektor.y = this->yCoord;
    return tempVektor;
}

bool grassTile::isValidTile(int const&towerType)
{
    if(!hasTower && towerType != 3)
    {
        hasTower = true;
        return true;
    }
    else
    {
        return false;
    }
}



waterTile::waterTile(int const&x, int const&y, sf::Vector2f const&position, float const&textureDim, float const&worldDim, sf::Texture texture) : Tile(x,y,position,textureDim,worldDim,texture)
{						       
}

void waterTile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Tile::draw(target,states);
}

sf::Vector2i waterTile::getCoords() const
{
    sf::Vector2i tempVektor;
    tempVektor.x = this->xCoord;
    tempVektor.y = this->yCoord;
    return tempVektor;
}

bool waterTile::isValidTile(int const&towerType)
{
    if(!hasTower && towerType == 3) //waterTile kan endast bygga vattentorn. Därför måste towerType vara 3 för att det ska vara valid.
    {
        hasTower = true;
        return true;
    }
    else
    {
        return false;
    }
}



pathTile::pathTile(int const&x, int const&y, sf::Vector2f const&position, float const&textureDim, float const&worldDim, sf::Texture texture) : Tile(x,y,position,textureDim,worldDim,texture)
{
    hasTower = true;
}

void pathTile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    Tile::draw(target,states);
}

sf::Vector2i pathTile::getCoords() const
{
    sf::Vector2i tempVektor;
    tempVektor.x = this->xCoord;
    tempVektor.y = this->yCoord;
    return tempVektor;
}

bool pathTile::isValidTile(int const&towerType)//Ska aldrig kunna ha torn på sig
{
    return false;
}



menuTile::menuTile(int const&x, int const&y, sf::Vector2f const&position, float const&textureDim, float const&worldDim, sf::Texture texture) : Tile(x,y,position,textureDim,worldDim,texture)
{
    hasTower = true;
}

void menuTile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{  
    Tile::draw(target,states);
}

sf::Vector2i menuTile::getCoords() const
{
    sf::Vector2i tempVektor;
    tempVektor.x = this->xCoord;
    tempVektor.y = this->yCoord;
    return tempVektor;
}

bool menuTile::isValidTile(int const&towerType) //Ska heller aldrig kunna ha torn på sig. 
{
    return false;
}
