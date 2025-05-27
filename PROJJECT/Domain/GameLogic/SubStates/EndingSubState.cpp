#include "EndingSubState.h"
#include "../../States/StateContext.h"
#include "../../States/MenuState.h"
#include <iostream>

EndingSubState::EndingSubState(GameState& gameState, bool goodEnding)
    : SubState(gameState) {

    auto& font = gameState.getContext().getResourceManager().getFont();
    auto& window = gameState.getContext().getWindow();

    std::string textureKey;
    if (goodEnding) {
        textureKey = "good_end";
        dialogueLines = {
            "YEAH! I'm alive!",
            "This is a victory.",
            "That harpy was a most dangerous opponent.",
            "And all the others I had to fight could have killed me.",
            "But I did it.",
            "And all the hardship was worth it, because I have Arcamun!",
            "And now I can save everyone.",
            "But on Monday.",
            "I'm tired for today, I'm going to lie down."
        };
    }
    else {
        textureKey = "bad_end";
        dialogueLines = {
            "No...",
            "Are those tears?"
            "Did I let everyone down?",
            "But I tried.",
            "I sent a letter that Arcamun is probably here.",
            "They'll probably send someone else.",
            "I hope he has better luck than me.",
            "I'm sorry...",
        };
    }

    endingText.setFont(font);
    endingText.setCharacterSize(50);
    endingText.setFillColor(sf::Color::White);
    endingText.setString(dialogueLines[0]);

    sf::FloatRect textRect = endingText.getLocalBounds();
    endingText.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
    endingText.setPosition(window.getSize().x / 2.f, window.getSize().y - 100.f);

    auto& texture = gameState.getContext().getResourceManager().getTexture(textureKey);
    background.setTexture(texture);

    float scaleX = static_cast<float>(window.getSize().x) / texture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / texture.getSize().y;
    background.setScale(scaleX, scaleY);
}

void EndingSubState::handleInput(sf::Event& event) {
    auto& window = gameState.getContext().getWindow();

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                gameState.getContext().pushState(std::make_unique<PauseState>(gameState.getContext()));
            }

            if (event.key.code == sf::Keyboard::Space) {
                currentLine++;
                if (currentLine < dialogueLines.size()) {
                    endingText.setString(dialogueLines[currentLine]);
                    sf::FloatRect textRect = endingText.getLocalBounds();
                    endingText.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
                }
                else {
                    gameState.getContext().changeState(std::make_unique<MenuState>(gameState.getContext()));
                }
            }
        }
    }
}

void EndingSubState::update() {}

void EndingSubState::render() {
    auto& window = gameState.getContext().getWindow();
    window.draw(background);
    window.draw(endingText);
}
