#pragma once
#include <SFML/Graphics.hpp>
#include "../../External/json.hpp"

using json = nlohmann::json;

class ResourceManager {
public:
    ResourceManager();

    sf::Font& getFont();
    sf::Texture& getTexture(const std::string& name);

private:
    sf::Font font;
    std::map<std::string, sf::Texture> textures;
};
