#include "MenuState.h"
#include "GameState.h"

MenuState::MenuState(StateContext& context) : State(context) {
    auto& font = context.getResourceManager().getFont();
    auto& window = context.getWindow();

    titleText.setFont(font);
    titleText.setString("Press Enter to Start");
    titleText.setCharacterSize(64);
    titleText.setFillColor(sf::Color::White);

    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
    titleText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
}

void MenuState::handleInput() {
    auto& window = context.getWindow();
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            context.changeState(std::make_unique<GameState>(context));
        }
    }
}

void MenuState::update() {}

void MenuState::render() {
    context.getWindow().draw(titleText);
}