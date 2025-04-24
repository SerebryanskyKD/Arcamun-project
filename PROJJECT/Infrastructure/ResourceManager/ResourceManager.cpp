#include "ResourceManager.h"

ResourceManager::ResourceManager() {
    if (!font.loadFromFile("chilispepper.ttf")) {
        throw std::runtime_error("Не удалось загрузить шрифт");
    }
}

sf::Font& ResourceManager::getFont() {
    return font;
}
