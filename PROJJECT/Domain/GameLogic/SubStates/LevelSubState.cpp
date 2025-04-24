#include "LevelOneSubState.h"
#include "../../States/StateContext.h"

LevelOneSubState::LevelOneSubState(GameState& gameState) : SubState(gameState) {
    auto& font = gameState.getContext().getResourceManager().getFont();
    auto& window = gameState.getContext().getWindow();

    levelText.setFont(font);
    levelText.setString("The first level of the dungeon");
    levelText.setCharacterSize(64);
    levelText.setFillColor(sf::Color::White);

    sf::FloatRect textRect = levelText.getLocalBounds();
    levelText.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
    levelText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
}

void LevelOneSubState::handleInput(sf::Event& event) {
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

void LevelOneSubState::update() {
    // Пока ничего не обновляется
}

void LevelOneSubState::render() {
    gameState.getContext().getWindow().draw(levelText);
}
