#include "ResourceManager.h"

ResourceManager::ResourceManager() {
    if (!font.loadFromFile("chilispepper.ttf")) {
        throw std::runtime_error("�� ������� ��������� �����");
    }
}

sf::Font& ResourceManager::getFont() {
    return font;
}
