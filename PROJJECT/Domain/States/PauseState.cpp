#include "PauseState.h"
#include "GameState.h"

PauseState::PauseState(StateContext& context) : State(context) {
    auto& font = context.getResourceManager().getFont();
    auto& window = context.getWindow();

    pauseText.setFont(font);
    pauseText.setString("Paused. Press Enter to resume.");
    pauseText.setCharacterSize(48);
    pauseText.setFillColor(sf::Color::Blue);

    sf::FloatRect textRect = pauseText.getLocalBounds();
    pauseText.setOrigin(textRect.width / 2, textRect.height / 2);
    pauseText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    auto& texture = context.getResourceManager().getTexture("pause");
    background.setTexture(texture);

    sf::Vector2u windowSize = context.getWindow().getSize();
    sf::Vector2u textureSize = texture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    background.setScale(scaleX, scaleY);
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
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
    }
}

void PauseState::update() {}

void PauseState::render() {
    context.getWindow().draw(background);
}