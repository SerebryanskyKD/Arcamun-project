#include "LevelCombatPhase.h"
#include "LevelSubState.h"
#include "EndingSubState.h"
#include <iostream>

LevelCombatPhase::LevelCombatPhase(GameState& gameState, int level) : gameState(gameState), player(gameState.getPlayer()),
    monster(level, gameState.getContext().getResourceManager().getTexture("monster_" + std::to_string(level)), 100 * level), level(level),
    notificationManager(gameState.getContext().getResourceManager().getFont(), sf::Vector2f( static_cast<float>(gameState.getContext().getWindow().getSize().x) / 2.f, 50.f))
{
    std::string bgKey = "level_" + std::to_string(level);
    auto& bgTexture = gameState.getContext().getResourceManager().getTexture(bgKey);
    background.setTexture(bgTexture);

    sf::Vector2f windowSize(gameState.getContext().getWindow().getSize());
    sf::Vector2f textureSize(bgTexture.getSize());
    background.setScale(windowSize.x / textureSize.x, windowSize.y / textureSize.y);

    auto& res = gameState.getContext().getResourceManager();
    float scale = 0.5f;

    attackButton = std::make_unique<ImageButton>(res.getTexture("bump"), sf::Vector2f(windowSize.x/2 - 400.f, windowSize.y - 270.f), 0.25);

    searchButton = std::make_unique<ImageButton>(res.getTexture("search"), sf::Vector2f(windowSize.x/2 + 0.f, windowSize.y - 270.f), 0.25);
}

void LevelCombatPhase::handleInput(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePosI = sf::Mouse::getPosition(gameState.getContext().getWindow());
        sf::Vector2f mousePos(static_cast<float>(mousePosI.x), static_cast<float>(mousePosI.y));

        player.handleInventoryClick(mousePos);

        if (attackButton && attackButton->isClicked(mousePosI)) {
            int playerDamage = player.getStats().strength;
            monster.takeDamage(playerDamage);

            if (!monster.isDead()) {
                int monsterDamage = level * 15;
                if (Probability::instance().roll(25.0f)) {
                    notificationManager.add("You ducked!");
                }
                else {
                    if (Probability::instance().roll(15.0f)) {
                        notificationManager.add("A critical hit for you!");
                        monsterDamage *= 2.5;
                    }
                    player.takeDamage(monsterDamage);
                }
            }

            if (monster.isDead()) {
                finished = true;
                if (level == 1) {
                    const auto& weaponData = gameState.getContext().getResourceManager().getJSON("weapons")["staff"];

                    player.getInventory().addWeapon(Weapon(
                        weaponTypeFromString(weaponData["type"]),
                        weaponData["name"],
                        weaponData["attack"],
                        weaponData["defense"],
                        weaponData["intuition"],
                        weaponData["perception"],
                        &gameState.getContext().getResourceManager().getTexture("staff")
                    ));

                    player.updateInventoryIcons();
                }
                if (level == 2) {
                    const auto& weaponData = gameState.getContext().getResourceManager().getJSON("weapons")["staff_magic"];

                    player.getInventory().addWeapon(Weapon(
                        weaponTypeFromString(weaponData["type"]),
                        weaponData["name"],
                        weaponData["attack"],
                        weaponData["defense"],
                        weaponData["intuition"],
                        weaponData["perception"],
                        &gameState.getContext().getResourceManager().getTexture("staff_magic")
                    ));
                    player.updateInventoryIcons();
                }
            }
        }

        if (searchButton && searchButton->isClicked(mousePosI)) {
            float escapeChance = static_cast<float>(player.getStats().intuition);

            if (level != 3 & Probability::instance().roll(escapeChance)) {
                notificationManager.add("Passage found!");
                finished = true;
            }
            else {
                int monsterDamage = level * 10;
                player.takeDamage(monsterDamage);

                float perceptionChance = static_cast<float>(player.getStats().perception * 2);

                if (Probability::instance().roll(perceptionChance)) {
                    int potionTypeIndex = Probability::instance().range(0, 4);
                    Potion::Type potionType = static_cast<Potion::Type>(potionTypeIndex);

                    std::string name;
                    std::string textureKey;

                    switch (potionType) {
                    case Potion::Type::Strength:
                        name = "Strength Potion";
                        textureKey = "potion_strength";
                        break;
                    case Potion::Type::Defense:
                        name = "Defense Potion";
                        textureKey = "potion_defense";
                        break;
                    case Potion::Type::Perception:
                        name = "Perception Potion";
                        textureKey = "potion_perception";
                        break;
                    case Potion::Type::Intuition:
                        name = "Intuition Potion";
                        textureKey = "potion_intuition";
                        break;
                    case Potion::Type::Health:
                        name = "Health Potion";
                        textureKey = "potion_health";
                        break;
                    }

                    sf::Texture& texture = gameState.getContext().getResourceManager().getTexture(textureKey);
                    player.getInventory().addPotion(Potion(potionType, name, 1, &texture));
                    player.updateInventoryIcons();
                    notificationManager.add("You found a " + name + "!");
                }
            }
        }
    }
}

void LevelCombatPhase::update() {
    if (playerDied) return;

    player.updateUI();

    if (player.isDead()) {
        playerDied = true;
        gameState.changeSubState(std::make_unique<EndingSubState>(gameState, 0));
        return;
    }

    float dt = deltaClock.restart().asSeconds();
    notificationManager.update(dt);
}

void LevelCombatPhase::render(sf::RenderWindow& window) {
    window.draw(background);
    monster.render(window);
    player.render(window);
    if (attackButton) attackButton->draw(window);
    if (searchButton) searchButton->draw(window);
    notificationManager.render(window);
}


bool LevelCombatPhase::isFinished() const {
    return finished;
}
