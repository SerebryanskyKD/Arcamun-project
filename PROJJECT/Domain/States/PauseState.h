#pragma once

#include "State.h"

class PauseState : public State {
public:
    explicit PauseState(StateContext& context);
    void handleInput() override;
    void update() override;
    void render() override;

private:
    sf::Text pauseText;
};