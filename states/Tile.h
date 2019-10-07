#pragma once
#include <SFML/Graphics.hpp>
#include "Tower.h"

class Tile : public sf::Drawable, public sf::Transformable
{
public:
    Tile();
    Tile(int const& x, int const& y, sf::Vector2f const& position, float const& textureDim, float const& worldDim, sf::Texture texture);
    virtual ~Tile() = default;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual sf::Vector2i getCoords() const = 0;
    virtual bool isValidTile(int const&towerType) = 0;

protected:
    int xCoord;
    int yCoord;
    sf::VertexArray tileDimensions;
    sf::Texture tileTexture;
    bool hasTower = false;
};

class sandTile : public Tile
{
public:
    sandTile( int const& x, int const& y, sf::Vector2f const& position, float const&textureDim, float const&worldDim, sf::Texture texture );
    ~sandTile() = default;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::Vector2i getCoords() const override;
    bool isValidTile(int const&towerType) override;
};

class grassTile : public Tile
{
public:
    grassTile( int const&x, int const&y, sf::Vector2f const&position, float const&textureDim, float const&worldDim, sf::Texture texture );
    ~grassTile() = default;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::Vector2i getCoords() const override;
    bool isValidTile(int const&towerType) override;
};

class waterTile : public Tile
{
public:
    waterTile( int const&x, int const&y, sf::Vector2f const&position, float const&textureDim, float const&worldDim, sf::Texture texture );
    ~waterTile() = default;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::Vector2i getCoords() const override;
    bool isValidTile(int const&towerType) override;
};

class pathTile : public Tile
{
public:
    pathTile( int const&x, int const&y, sf::Vector2f const&position, float const&textureDim, float const&worldDim, sf::Texture texture );
    ~pathTile() = default;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::Vector2i getCoords() const override;
    bool isValidTile(int const&towerType) override;
};

class menuTile : public Tile
{
public:
    menuTile( int const&x, int const&y, sf::Vector2f const&position, float const&textureDim, float const&worldDim, sf::Texture texture );
    ~menuTile() = default;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::Vector2i getCoords() const override;
    bool isValidTile(int const&towerType) override;
};
