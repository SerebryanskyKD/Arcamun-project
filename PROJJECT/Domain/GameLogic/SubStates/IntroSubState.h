#pragma once
#include "SubState.h"

class IntroSubState : public SubState {
public:
    IntroSubState(GameState& gameState);

    void handleInput(sf::Event& event) override;
    void update() override;
    void render() override;

private:
    sf::Text dialogueText;
};
