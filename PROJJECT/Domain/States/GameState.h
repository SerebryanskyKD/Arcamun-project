#pragma once

#include <memory>
#include "State.h"
//#include "../GameLogic/SubStates/SubState.h"

class Player;
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

private:
    std::unique_ptr<SubState> currentSubState;
};
