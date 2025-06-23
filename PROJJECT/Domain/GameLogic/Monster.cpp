#include "Monster.h"

Monster::Monster(int level, const sf::Texture& texture, int maxHP) : level(level), maxHP(maxHP), hp(maxHP)
{
    sf::Vector2u windowSize = sf::Vector2u(1920, 1080);

    float desiredWidth = windowSize.x / 5.f;
    float scale = desiredWidth / texture.getSize().x;

    sprite.setTexture(texture);

    if (level == 1) {
        sprite.setScale(scale * 0.6, scale * 0.6);
    }
    else {
        sprite.setScale(scale, scale);
    }
    

    sf::FloatRect bounds = sprite.getGlobalBounds();
    if (level == 3) {
        sprite.setPosition(
            windowSize.x / 2.f - bounds.width / 2.f,
            windowSize.y / 2.f - bounds.height / 1.f
        );
    }
    else if (level == 1) {
        sprite.setPosition(
            windowSize.x / 2.f - bounds.width / 2.f,
            windowSize.y / 2.f - bounds.height / 4.f
        );
    }
    else {
        sprite.setPosition(
            windowSize.x / 2.f - bounds.width / 2.f,
            windowSize.y / 2.f - bounds.height / 2.f
        );
    }

    float barWidth = bounds.width;
    float barHeight = 20.f;

    hpBarBack.setSize({ barWidth, barHeight });
    hpBarBack.setFillColor(sf::Color::Red);
    hpBarBack.setPosition(sprite.getPosition().x, sprite.getPosition().y - barHeight - 5.f);

    hpBarFront.setSize({ barWidth, barHeight });
    hpBarFront.setFillColor(sf::Color::Green);
    hpBarFront.setPosition(hpBarBack.getPosition());
}

void Monster::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
    updateHPBar();
}

void Monster::updateHPBar() {
    float percent = static_cast<float>(hp) / maxHP;
    float fullWidth = hpBarBack.getSize().x;
    hpBarFront.setSize({ fullWidth * percent, hpBarBack.getSize().y });
}

void Monster::render(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(hpBarBack);
    window.draw(hpBarFront);
}

bool Monster::isDead() const {
    return hp <= 0;
}
