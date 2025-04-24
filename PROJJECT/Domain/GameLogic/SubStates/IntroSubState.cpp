#include "IntroSubState.h"
#include "../../States/StateContext.h"
#include "LevelOneSubState.h" // пока не реализован, но понадобится

IntroSubState::IntroSubState(GameState& gameState) : SubState(gameState) {
    auto& font = gameState.getContext().getResourceManager().getFont();
    auto& window = gameState.getContext().getWindow();

    introText.setFont(font);
    introText.setString("You're standing in front of the entrance to the dungeon...\nPress Enter to enter.");
    introText.setCharacterSize(64);
    introText.setFillColor(sf::Color::White);

    sf::FloatRect textRect = introText.getLocalBounds();
    introText.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
    introText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
}

void IntroSubState::handleInput(sf::Event& event) {
    auto& window = gameState.getContext().getWindow();
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            gameState.getContext().pushState(std::make_unique<PauseState>(gameState.getContext()));
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
            gameState.changeSubState(std::make_unique<LevelOneSubState>(gameState));
        }
    }
}

void IntroSubState::update() {
    // Пока ничего не обновляется
}

void IntroSubState::render() {
    gameState.getContext().getWindow().draw(introText);
}
