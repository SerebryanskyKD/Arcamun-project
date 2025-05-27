#pragma once

#include <memory>
#include "State.h"
#include "../GameLogic/Player.h"

class StateContext;
class SubState;

class GameState : public State {
public:
    explicit GameState(StateContext& context);

    void handleInput() override;
    void update() override;
    void render() override;

    void changeSubState(std::unique_ptr<SubState> newSubState);

    StateContext& getContext();
    Player& getPlayer();

private:
    std::unique_ptr<SubState> currentSubState;
    std::unique_ptr<SubState> nextSubState;
    Player player;
};
