#include "GameState.h"
#include "../GameLogic/SubStates/IntroSubState.h"

GameState::GameState(StateContext& context) : State(context)
{
    auto& font = context.getResourceManager().getFont();
    auto& window = context.getWindow();
    changeSubState(std::make_unique<IntroSubState>(*this));
}


void GameState::handleInput() {
    auto& window = context.getWindow();
    sf::Event event;
    if (currentSubState) {
        currentSubState->handleInput(event);
    }
}

void GameState::update() {
    if (currentSubState) {
        currentSubState->update();
    }
}

void GameState::render() {
    auto& window = context.getWindow();
    if (currentSubState) {
        currentSubState->render();
    }
}


void GameState::changeSubState(std::unique_ptr<SubState> newSubState) {
    currentSubState = std::move(newSubState);
}

StateContext& GameState::getContext() {
    return context;
}
