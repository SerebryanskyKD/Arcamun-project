#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include "../Domain/States/State.h"
#include "../Infrastructure/ResourceManager/ResourceManager.h"
#include "../Domain/States/StateContext.h"

class Game : public StateContext {
public:
    Game();
    void init();
    void run();
    void changeState(std::unique_ptr<State> newState) override;
    void pushState(std::unique_ptr<State> newState) override;
    void popState() override;

    sf::RenderWindow& getWindow() override;
    ResourceManager& getResourceManager() override;

private:
    void handleInput();
    void update();
    void render();

    const float BASE_WIDTH = 1920.0f;
    const float BASE_HEIGHT = 1080.0f;

    float scaleX;
    float scaleY;
    float scale;

    sf::RenderWindow window;
    std::stack<std::unique_ptr<State>> stateStack;
    std::unique_ptr<State> pendingState;
    bool shouldPop = false;
    bool shouldChange = false;
    ResourceManager resourceManager;
};