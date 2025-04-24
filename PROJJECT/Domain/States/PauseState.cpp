#include "PauseState.h"
#include "GameState.h"

PauseState::PauseState(StateContext& context) : State(context) {
    auto& font = context.getResourceManager().getFont();
    auto& window = context.getWindow();

    pauseText.setFont(font);
    pauseText.setString("Paused. Press Enter to resume.");
    pauseText.setCharacterSize(48);
    pauseText.setFillColor(sf::Color::Yellow);

    sf::FloatRect textRect = pauseText.getLocalBounds();
    pauseText.setOrigin(textRect.width / 2, textRect.height / 2);
    pauseText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
}

void PauseState::handleInput() {
    auto& window = context.getWindow();
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            context.popState();
            //return;
        }
    }
}

void PauseState::update() {}

void PauseState::render() {
    context.getWindow().draw(pauseText);
}