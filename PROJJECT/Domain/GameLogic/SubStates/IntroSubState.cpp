#include "IntroSubState.h"
#include "../../States/StateContext.h"
#include "LevelSubState.h"

IntroSubState::IntroSubState(GameState& gameState) : SubState(gameState) {
    auto& font = gameState.getContext().getResourceManager().getFont();
    auto& window = gameState.getContext().getWindow();

    dialogueText.setFont(font);
    dialogueText.setCharacterSize(50);
    dialogueText.setFillColor(sf::Color::White);
    dialogueLines = {
    "...",
    "I finally made it to this dungeon.",
    "According to my friend's message, there may be an Arcamun in it!",
    "But where is he?",
    "Well, there's no time, I'll go alone.",
    "I have to get this treasure to save everyone."
    };
    dialogueText.setString(dialogueLines[0]);

    sf::FloatRect textRect = dialogueText.getLocalBounds();
    dialogueText.setOrigin(textRect.width / 2.f, textRect.height / 2.f);

    dialogueText.setPosition(
        window.getSize().x / 2.f,
        window.getSize().y - 100.f
    );

    auto& texture = gameState.getContext().getResourceManager().getTexture("intro");
    background.setTexture(texture);

    sf::Vector2u windowSize = gameState.getContext().getWindow().getSize();
    sf::Vector2u textureSize = texture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    background.setScale(scaleX, scaleY);
}

void IntroSubState::handleInput(sf::Event& event) {
    auto& window = gameState.getContext().getWindow();

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            gameState.getContext().pushState(std::make_unique<PauseState>(gameState.getContext()));
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            currentLine++;
            if (currentLine < dialogueLines.size()) {
                dialogueText.setString(dialogueLines[currentLine]);
                sf::FloatRect textRect = dialogueText.getLocalBounds();
                dialogueText.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
            }
            else {
                gameState.changeSubState(std::make_unique<LevelSubState>(gameState, 1));
            }
        }

    }
}

void IntroSubState::update() {}

void IntroSubState::render() {
    gameState.getContext().getWindow().draw(background);
    gameState.getContext().getWindow().draw(dialogueText);
}
