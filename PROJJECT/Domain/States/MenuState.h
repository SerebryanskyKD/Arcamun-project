#pragma once

#include "State.h"

class MenuState : public State {
public:
    explicit MenuState(StateContext& context);
    void handleInput() override;
    void update() override;
    void render() override;

private:
    sf::Text titleText;
    //sf::Sprite background;
};