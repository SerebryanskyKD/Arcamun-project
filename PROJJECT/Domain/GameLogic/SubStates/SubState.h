#pragma once
#include <SFML/Graphics.hpp>
#include "../../States/GameState.h"
#include "../../States/PauseState.h"

class SubState {
public:
    explicit SubState(GameState& gameState) : gameState(gameState) {}
    virtual ~SubState() = default;

    virtual void handleInput(sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void render() = 0;

protected:
    GameState& gameState;
};
