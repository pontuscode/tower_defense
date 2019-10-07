#include "assetManager.h"

//tar in en keytype och en valuetype i form av strängar. 
void assetManager::loadTexture(std::string const& name, std::string const& fileName)

{
    if (textures.find(name) != end(textures) )
        return;           //om nyckeln redan finns i mappen laddar vi inte in den igen
    sf::Texture texture;
    if(texture.loadFromFile(fileName))
    {
        this->textures[name] = texture;
    }
}


//returnerar en referens till texturen som är knuten till nyckeln
sf::Texture &assetManager::getTexture(std::string const& name)

{
    return this->textures.at(name);
}



void assetManager::loadFont(std::string const& name, std::string const& fileName)

{
    sf::Font font;
    if(font.loadFromFile(fileName))
    {
        this->fonts[name] = font;
    }
}

sf::Font &assetManager::getFont(std::string const& name)
{
    return this->fonts.at(name);
}
