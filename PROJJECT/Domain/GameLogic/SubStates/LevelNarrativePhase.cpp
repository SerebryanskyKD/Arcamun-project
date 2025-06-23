#include "LevelNarrativePhase.h"

LevelNarrativePhase::LevelNarrativePhase(GameState& gameState, int level, bool isPostCombat) : gameState(gameState)
{
    setupLinesForLevel(level, isPostCombat);

    auto& font = gameState.getContext().getResourceManager().getFont();
    auto& window = gameState.getContext().getWindow();

    dialogueText.setFont(font);
    dialogueText.setCharacterSize(48);
    dialogueText.setFillColor(sf::Color::White);

    if (!lines.empty()) {
        dialogueText.setString(lines[0]);
    }

    sf::FloatRect textRect = dialogueText.getLocalBounds();
    dialogueText.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
    dialogueText.setPosition(window.getSize().x / 2.f, window.getSize().y - 100.f);

    std::string textureKey = "level_" + std::to_string(level);
    auto& texture = gameState.getContext().getResourceManager().getTexture(textureKey);
    background.setTexture(texture);

    sf::Vector2u windowSize = gameState.getContext().getWindow().getSize();
    sf::Vector2u textureSize = texture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    background.setScale(scaleX, scaleY);
}


void LevelNarrativePhase::handleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        advanceLine();
    }
}

void LevelNarrativePhase::update() {}

void LevelNarrativePhase::render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(dialogueText);
}

bool LevelNarrativePhase::isFinished() const {
    return finished;
}

void LevelNarrativePhase::advanceLine() {
    if (currentLine + 1 < lines.size()) {
        currentLine++;
        dialogueText.setString(lines[currentLine]);
        sf::FloatRect textRect = dialogueText.getLocalBounds();
        dialogueText.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
    }
    else {
        finished = true;
    }
}

void LevelNarrativePhase::setupLinesForLevel(int level, bool isPostCombat) {
    const auto& dialogues = gameState.getContext().getResourceManager().getJSON("dialogues");

    if (!isPostCombat)
        lines = dialogues["levels"][std::to_string(level)]["pre"].get<std::vector<std::string>>();
    else
        lines = dialogues["levels"][std::to_string(level)]["post"].get<std::vector<std::string>>();

}
