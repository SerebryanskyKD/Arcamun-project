#pragma once
#include "SubState.h"

class EndingSubState : public SubState {
public:
    EndingSubState(GameState& gameState, bool goodEnding);

    void handleInput(sf::Event& event) override;
    void update() override;
    void render() override;

private:
    sf::Text endingText;
};