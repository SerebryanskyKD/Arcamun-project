#pragma once
#include <string>
#include <vector>
#include "InventoryItem.h"
#include <../../External/json.hpp>

class GameState;

struct Stats {
    int health, maxHealth, strength, defense, intuition, perception;

    void applyBonuses(const Weapon& weapon) {
        strength += weapon.attackBonus;
        defense += weapon.defenseBonus;
        intuition += weapon.intuitionBonus;
        perception += weapon.perceptionBonus;
    }

    void removeBonuses(const Weapon& weapon) {
        strength -= weapon.attackBonus;
        defense -= weapon.defenseBonus;
        intuition -= weapon.intuitionBonus;
        perception -= weapon.perceptionBonus;
    }

    void loadFromJSON(const nlohmann::json& json) {
        if (json.contains("health")) health = json["health"];
        if (json.contains("maxHealth")) maxHealth = json["maxHealth"];
        if (json.contains("strength")) strength = json["strength"];
        if (json.contains("defense")) defense = json["defense"];
        if (json.contains("intuition")) intuition = json["intuition"];
        if (json.contains("perception")) perception = json["perception"];
    }
};

class Inventory {
public:
    void addWeapon(const Weapon& weapon) {
        weapons.push_back(weapon);
    }

    void addPotion(const Potion& potion) {
        for (auto& p : potions) {
            if (p.type == potion.type) {
                p.amount += potion.amount;
                return;
            }
        }
        potions.push_back(potion);
    }

    const std::vector<Weapon>& getWeapons() const {
        return weapons;
    }

    const std::vector<Potion>& getPotions() const {
        return potions;
    }

private:
    std::vector<Weapon> weapons;
    std::vector<Potion> potions;
};


struct ClickableInventoryItem {
    const Weapon* weapon;
    sf::Sprite icon;
    bool selected = false;

    bool contains(const sf::Vector2f& point) const {
        return icon.getGlobalBounds().contains(point);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(icon);
        if (selected) {
            sf::FloatRect bounds = icon.getGlobalBounds();

            sf::RectangleShape outline;
            outline.setSize({ bounds.width, bounds.height });
            outline.setPosition(bounds.left, bounds.top);
            outline.setFillColor(sf::Color::Transparent);
            outline.setOutlineColor(sf::Color(200, 200, 255, 100));
            outline.setOutlineThickness(1.f);

            window.draw(outline);
        }
    }
};

struct ClickablePotionItem {
    const Potion* potion;
    sf::Sprite icon;
    sf::Text amountText;

    void updateText() {
        if (!potion) return;
        amountText.setString("x" + std::to_string(potion->amount));
        amountText.setCharacterSize(150);
        amountText.setFillColor(sf::Color::White);

        sf::FloatRect bounds = icon.getGlobalBounds();
        amountText.setPosition(bounds.left + bounds.width - 30.f, bounds.top + bounds.height - 30.f);

        float scale = icon.getScale().x;
        amountText.setScale(scale, scale);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(icon);
        window.draw(amountText);
    }
};

class Player {
public:
    explicit Player(GameState& gameState);

    Stats& getStats();
    const Weapon& getWeapon() const;

    void equipWeapon(const Weapon& newWeapon);
    void takeDamage(int dmg);
    bool isDead() const;

    Inventory& getInventory();
    void updateInventoryIcons();

    void initUI();
    void updateUI();
    void handleInventoryClick(const sf::Vector2f& clickPosition);
    void render(sf::RenderWindow& window);

    int getBaseStrength() const;
    int getWeaponStrengthBonus() const;

    int getBaseDefense() const;
    int getWeaponDefenseBonus() const;

    int getBaseIntuition() const;
    int getWeaponIntuitionBonus() const;

    int getBasePerception() const;
    int getWeaponPerceptionBonus() const;

    int getMaxHealth() const;
    int getCurrentHealth() const;

private:
    GameState& gameState;
    Stats baseStats;
    Weapon equippedWeapon;
    Inventory inventory;
    std::vector<ClickableInventoryItem> weaponIcons;
    std::vector<ClickablePotionItem> potionIcons;

    std::vector<sf::Text> statTexts;
    sf::RectangleShape hpBarBack;
    sf::RectangleShape hpBarFront;

    bool uiInitialized = false;
    
};
