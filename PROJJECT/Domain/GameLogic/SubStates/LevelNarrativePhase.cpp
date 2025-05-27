#include "LevelNarrativePhase.h"

LevelNarrativePhase::LevelNarrativePhase(GameState& gameState, int level, bool isPostCombat)
    : gameState(gameState)
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
    if (!isPostCombat) {
        switch (level) {
        case 1: lines = { "I must be careful.", "A lot of people who come in here don't come back.", "Well, I can find a lot of useful things on earth if I look.", "Wait, is that skeleton moving?", "Basically I can try to find a way out and rush past him.", "But then I'd miss the opportunity to find a useful weapon.", "Okay, I'll decide during the fight.", "It's attacking!" }; break;
        case 2: lines = { "These columns have been here a long time. But who lit them?", "Oh, a goblin, of course. There's always one in a place like this.", "He'll be harder to fight than a skeleton puppet." }; break;
        case 3: lines = { "This is the deepest part of the dungeon.", "Is there lava underneath me?", "It's hard for me to see or breathe.", "But I feel like that's not the problem.", "Oh? Oh, no. Harpy?", "She's holding an Arcamun!", "I can't just run away like that!"}; break;
        }
    }
    else {
        switch (level) {
        case 1: lines = { "Ughhhh... There really might be a treasure here.", "Otherwise, the skeleton wouldn't have come to life to protect it." }; break;
        case 2: lines = { "I hate those green crows.", "Always getting in the way.", "And because they're greedy, they'll do anything.", "I could have died because of him!", "Well, okey. Now I'm ready to go all the way." }; break;
        case 3: lines = { "...", "I can't believe it myself, but..." }; break;
        }
    }
}
