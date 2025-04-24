#pragma once
#include "SubState.h"
#include <SFML/Graphics.hpp>

class LevelOneSubState : public SubState {
public:
    LevelOneSubState(GameState& gameState);

    void handleInput(sf::Event& event) override;
    void update() override;
    void render() override;

private:
    sf::Text levelText;
};