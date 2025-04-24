#include "Game.h"
#include "../Domain/States/MenuState.h"
#include "../Domain/States/GameState.h"
#include "../Domain/States/PauseState.h"

Game::Game() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    float screenWidth = static_cast<float>(desktop.width);
    float screenHeight = static_cast<float>(desktop.height);

    window.create(sf::VideoMode(static_cast<unsigned int>(screenWidth),
        static_cast<unsigned int>(screenHeight)),
        "Arcamon");

    scaleX = screenWidth / BASE_WIDTH;
    scaleY = screenHeight / BASE_HEIGHT;
    scale = std::min(scaleX, scaleY);
}

void Game::init() {
    changeState(std::make_unique<MenuState>(*this));
}

void Game::changeState(std::unique_ptr<State> newState) {
    pendingState = std::move(newState);
    shouldPop = true;
    shouldChange = true;
}

void Game::pushState(std::unique_ptr<State> newState) {
    pendingState = std::move(newState);
    shouldChange = true;
}

void Game::popState() {
    shouldPop = true;
    shouldChange = true;
}

void Game::run() {
    while (window.isOpen()) {
        if (shouldChange) {
            if (shouldPop && !stateStack.empty()) {
                stateStack.pop();
            }
            if (pendingState) {
                stateStack.push(std::move(pendingState));
            }
            shouldChange = false;
            shouldPop = false;
            //continue;
        }

        if (!stateStack.empty()) {
            handleInput();
            update();
            render();
        }
    }
}

void Game::handleInput() {
    stateStack.top()->handleInput();
}

void Game::update() {
    stateStack.top()->update();
}

void Game::render() {
    window.clear();
    stateStack.top()->render();
    window.display();
}

sf::RenderWindow& Game::getWindow() {
    return window;
}

ResourceManager& Game::getResourceManager() {
    return resourceManager;
}