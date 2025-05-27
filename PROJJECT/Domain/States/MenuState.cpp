#include "MenuState.h"
#include "GameState.h"

MenuState::MenuState(StateContext& context) : State(context) {
    auto& font = context.getResourceManager().getFont();
    auto& window = context.getWindow();

    titleText.setFont(font);
    titleText.setString("Press Enter to Start");
    titleText.setCharacterSize(64);
    titleText.setFillColor(sf::Color::Black);

    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setOrigin(textRect.width / 2.f, textRect.height / 2.f);

    titleText.setPosition(
        window.getSize().x / 2.f,
        window.getSize().y - 100.f
    );

    auto& texture = context.getResourceManager().getTexture("menu");
    background.setTexture(texture);

    sf::Vector2u windowSize = context.getWindow().getSize();
    sf::Vector2u textureSize = texture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    background.setScale(scaleX, scaleY);
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
    context.getWindow().draw(background);
}