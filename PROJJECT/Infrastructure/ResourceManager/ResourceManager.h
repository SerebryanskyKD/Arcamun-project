#pragma once
#include <SFML/Graphics.hpp>

class ResourceManager {
public:
    ResourceManager();

    sf::Font& getFont();

private:
    sf::Font font;
};
