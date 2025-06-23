#include "EndingSubState.h"
#include "../../States/StateContext.h"
#include "../../States/MenuState.h"
#include <iostream>

EndingSubState::EndingSubState(GameState& gameState, bool goodEnding) : SubState(gameState) {

    auto& font = gameState.getContext().getResourceManager().getFont();
    auto& window = gameState.getContext().getWindow();

    std::string textureKey;
    auto& j = gameState.getContext().getResourceManager().getJSON("dialogues");
    dialogueLines = j["ending"][goodEnding ? "good" : "bad"].get<std::vector<std::string>>();
    textureKey = goodEnding ? "good_end" : "bad_end";

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
