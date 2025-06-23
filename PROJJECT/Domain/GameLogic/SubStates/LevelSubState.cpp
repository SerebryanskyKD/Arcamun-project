#include "LevelSubState.h"
#include "LevelNarrativePhase.h"
#include "LevelCombatPhase.h"
#include "EndingSubState.h"


LevelSubState::LevelSubState(GameState& gameState, int level) : SubState(gameState), level(level), currentPhaseType(PhaseType::PreCombatNarrative) {
     startNextPhase();
}

void LevelSubState::handleInput(sf::Event& event) {
    auto& window = gameState.getContext().getWindow();
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            gameState.getContext().pushState(std::make_unique<PauseState>(gameState.getContext()));

        if (currentPhase)
            currentPhase->handleInput(event);
    }
}

void LevelSubState::update() {
    if (currentPhase) {
        currentPhase->update();
        if (currentPhase->isFinished())
            startNextPhase();
    }
}

void LevelSubState::render() {
    if (currentPhase)
        currentPhase->render(gameState.getContext().getWindow());
}

void LevelSubState::startNextPhase() {
    switch (currentPhaseType) {

    case PhaseType::PreCombatNarrative:
        currentPhase = std::make_unique<LevelNarrativePhase>(gameState, level, false);
        currentPhaseType = PhaseType::Combat;
        break;

    case PhaseType::Combat:
        currentPhase = std::make_unique<LevelCombatPhase>(gameState, level);
        currentPhaseType = PhaseType::PostCombatNarrative;
        break;

    case PhaseType::PostCombatNarrative:
        currentPhase = std::make_unique<LevelNarrativePhase>(gameState, level, true);

        currentPhaseType = PhaseType::PrepareNextLevel;
        break;

    case PhaseType::PrepareNextLevel:
        if (level < 3) {
            gameState.changeSubState(std::make_unique<LevelSubState>(gameState, level + 1));
        }
        else {
            gameState.changeSubState(std::make_unique<EndingSubState>(gameState, 1));
        }
        break;
    }
}
