#include "ResourceManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

ResourceManager::ResourceManager() {
    font.loadFromFile("chilispepper.ttf");

    textures["menu"].loadFromFile("menu.png");
    textures["pause"].loadFromFile("pause.png");
    textures["intro"].loadFromFile("intro.png");
    textures["level_1"].loadFromFile("level_1.png");
    textures["level_2"].loadFromFile("level_2.png");
    textures["level_3"].loadFromFile("level_3.png");
    textures["good_end"].loadFromFile("good_end.png");
    textures["bad_end"].loadFromFile("bad_end.png");
    textures["monster_1"].loadFromFile("monster_1.png");
    textures["monster_2"].loadFromFile("monster_2.png");
    textures["monster_3"].loadFromFile("monster_3.png");
    textures["potion_health"].loadFromFile("+hp.png");
    textures["potion_strength"].loadFromFile("potion_strength.png");
    textures["potion_defense"].loadFromFile("potion_defense.png");
    textures["potion_perception"].loadFromFile("potion_perception.png");
    textures["potion_intuition"].loadFromFile("potion_intuition.png");

    textures["sword_and_shield"].loadFromFile("sword_and_shield.png");
    textures["staff"].loadFromFile("staff.png");
    textures["staff_magic"].loadFromFile("staff_with_magic_stone.png");
    textures["bump"].loadFromFile("bump.png");
    textures["search"].loadFromFile("search.png");
}

sf::Font& ResourceManager::getFont() {
    return font;
}

sf::Texture& ResourceManager::getTexture(const std::string& name) {
    return textures.at(name);
}