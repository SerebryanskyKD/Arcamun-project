#pragma once
#include <SFML/Graphics.hpp>

class ImageButton {
public:
    ImageButton(const sf::Texture& texture, const sf::Vector2f& position, float scale) : visible(true)
    {
        sprite.setTexture(texture);
        sprite.setScale(scale, scale);
        sprite.setPosition(position);
    }

    void setVisible(bool v) { visible = v; }
    bool isVisible() const { return visible; }

    void draw(sf::RenderWindow& window) const {
        if (visible)
            window.draw(sprite);
    }

    bool isClicked(const sf::Vector2i& mousePos) const {
        if (!visible) return false;
        return sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

private:
    sf::Sprite sprite;
    bool visible;
};
