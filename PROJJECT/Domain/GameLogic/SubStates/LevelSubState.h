#pragma once
#include "SubState.h"
#include "../Monster.h"
#include "LevelPhase.h"

class LevelSubState : public SubState {
public:
    LevelSubState(GameState& gameState, int level);

    void handleInput(sf::Event& event) override;
    void update() override;
    void render() override;

private:
    int level;
    std::unique_ptr<LevelPhase> currentPhase;

    enum class PhaseType { PreCombatNarrative, Combat, PostCombatNarrative, PrepareNextLevel };
    PhaseType currentPhaseType = PhaseType::PreCombatNarrative;

    void startNextPhase();
};