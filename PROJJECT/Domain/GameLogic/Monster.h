#pragma once
#include <SFML/Graphics.hpp>

class Monster {
public:
    Monster(int level, const sf::Texture& texture, int maxHP);

    void takeDamage(int amount);
    void render(sf::RenderWindow& window);
    bool isDead() const;

private:
    int level;
    int hp;
    int maxHP;
    sf::Sprite sprite;
    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarFront;

    void updateHPBar();
};