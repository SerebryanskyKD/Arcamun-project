#pragma once
#include <memory>
#include "../../Infrastructure/ResourceManager/ResourceManager.h"

class State;

class StateContext {
public:
    virtual void changeState(std::unique_ptr<State> newState) = 0;
    virtual void pushState(std::unique_ptr<State> newState) = 0;
    virtual void popState() = 0;
    virtual sf::RenderWindow& getWindow() = 0;
    virtual ResourceManager& getResourceManager() = 0;
    virtual ~StateContext() = default;
};