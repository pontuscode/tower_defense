#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <string>


/*Asset managern används för att ladda in textures och fonts och liknande i     maps. Istället för att varje klass ska ladda in sina egna textures kan 
asset managern hålla koll på detta åt oss. Ska vi sedan bygga ett nytt 
sandTower kan vi helt enkelt bara kalla på exempelvis
sandTower.texture = assetManager.getTexture(sandTower);
*/

class assetManager
{
public: 
    assetManager() {}
    ~assetManager() = default;

    void loadTexture(std::string const& name, std::string const& fileName);
    sf::Texture &getTexture(std::string const& name);

    void loadFont(std::string const& name, std::string const& fileName);
    sf::Font &getFont(std::string const& name);
private:
    std::map <std::string, sf::Texture> textures;
    std::map <std::string, sf::Font> fonts;
};
