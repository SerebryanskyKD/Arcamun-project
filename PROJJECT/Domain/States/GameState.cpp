#include "GameState.h"
#include "../GameLogic/SubStates/IntroSubState.h"

GameState::GameState(StateContext& context) : State(context), player(*this) {
    player.initUI();
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
    if (currentSubState)
        currentSubState->update();

    if (nextSubState) {
        currentSubState = std::move(nextSubState);
    }
}

void GameState::render() {
    if (currentSubState) {
        currentSubState->render();
    }
}

void GameState::changeSubState(std::unique_ptr<SubState> newState) {
    nextSubState = std::move(newState);
}

StateContext& GameState::getContext() {
    return context;
}

Player& GameState::getPlayer() {
    return player;
}

