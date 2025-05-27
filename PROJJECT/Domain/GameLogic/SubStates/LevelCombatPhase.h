#pragma once
#include "LevelPhase.h"
#include "../Monster.h"
#include "../../States/GameState.h"
#include "../../UI/ImageButton.h"
#include "../Probability.h"
#include "../NotificationManager.h"


class LevelCombatPhase : public LevelPhase {
public:
    LevelCombatPhase(GameState& gameState, int level);

    void handleInput(sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;
    bool isFinished() const override;
    
    std::unique_ptr<ImageButton> attackButton;
    std::unique_ptr<ImageButton> searchButton;

private:
    GameState& gameState;
    Monster monster;
    Player& player;
    bool finished = false;
    int level;
    bool shouldTransition = false;
    bool playerDied = false;
    NotificationManager notificationManager;
    sf::Clock deltaClock;
};
