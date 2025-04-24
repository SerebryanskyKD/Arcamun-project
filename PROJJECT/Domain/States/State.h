#pragma once

#include <SFML/Graphics.hpp>
#include "StateContext.h"

class State {
public:
    explicit State(StateContext& context) : context(context) {}
    virtual ~State() = default;

    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void render() = 0;

protected:
    StateContext& context;
};
