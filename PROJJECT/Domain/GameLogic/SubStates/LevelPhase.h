#pragma once
#include <SFML/Graphics.hpp>

class LevelPhase {
public:
    virtual ~LevelPhase() = default;
    virtual void handleInput(sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool isFinished() const = 0;

protected:
    sf::Sprite background;
};
