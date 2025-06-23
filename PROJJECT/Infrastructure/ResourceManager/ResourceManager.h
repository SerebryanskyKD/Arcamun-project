#pragma once
#include <SFML/Graphics.hpp>
#include "../../External/json.hpp"

using json = nlohmann::json;

class ResourceManager {
public:
    ResourceManager();

    sf::Font& getFont();
    sf::Texture& getTexture(const std::string& name);
    void loadJSON(const std::string& key, const std::string& filename);
    const json& getJSON(const std::string& key) const;

private:
    sf::Font font;
    std::map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, json> jsonDataMap;
};
