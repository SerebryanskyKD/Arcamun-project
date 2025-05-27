#pragma once
#include "LevelPhase.h"
#include "../../States/GameState.h"
#include <vector>

class LevelNarrativePhase : public LevelPhase {
public:
    LevelNarrativePhase(GameState& gameState, int level, bool isPostCombat = false);

    void handleInput(sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override;

private:
    GameState& gameState;
    std::vector<std::string> lines;
    sf::Text dialogueText;
    size_t currentLine = 0;
    bool finished = false;

    void advanceLine();
    void setupLinesForLevel(int level, bool isPostCombat);
};
