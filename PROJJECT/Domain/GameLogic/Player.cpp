#include "Player.h"
#include "../States/GameState.h"
#include "../../Infrastructure/ResourceManager/ResourceManager.h"

Player::Player(GameState& gameState)
    : gameState(gameState),
    equippedWeapon(Weapon::Type::SwordAndShield,
        "Sword and Shield",
        6, 6, 0, 0,
        &gameState.getContext().getResourceManager().getTexture("sword_and_shield"))
{
    baseStats.applyBonuses(equippedWeapon);

    inventory.addWeapon(equippedWeapon);
}

Stats& Player::getStats() {
    return baseStats;
}

const Weapon& Player::getWeapon() const {
    return equippedWeapon;
}

void Player::equipWeapon(const Weapon& newWeapon) {
    baseStats.removeBonuses(equippedWeapon);
    equippedWeapon = newWeapon;
    baseStats.applyBonuses(equippedWeapon);
}

void Player::takeDamage(int dmg) {
    int actualDamage = std::max(0, dmg - baseStats.defense);
    baseStats.health = std::max(0, baseStats.health - actualDamage);
}

bool Player::isDead() const {
    return baseStats.health <= 0;
}

Inventory& Player::getInventory() {
    return inventory;
}

void Player::updateInventoryIcons() {
    weaponIcons.clear();
    potionIcons.clear();

    const auto& weapons = inventory.getWeapons();
    const auto& potions = inventory.getPotions();

    float padding = 32.f;
    float iconSize = 150.f;
    float x = padding;

    float columnSpacing = 5.f;

    // Оружие
    for (size_t i = 0; i < weapons.size(); ++i) {
        ClickableInventoryItem item;
        item.weapon = &weapons[i];

        item.icon.setTexture(*weapons[i].texture);
        float scale = iconSize / weapons[i].texture->getSize().x;
        item.icon.setScale(scale, scale);
        item.icon.setPosition(x, padding + i * (iconSize - iconSize / 100));
        item.selected = (&weapons[i] == &equippedWeapon);
        weaponIcons.push_back(std::move(item));
    }

    // Зелья
    int visiblePotionIndex = 0;
    for (const auto& potion : potions) {
        if (potion.amount <= 0) continue;

        ClickablePotionItem item;
        item.potion = &potion;

        item.icon.setTexture(*potion.texture);
        float scale = iconSize / potion.texture->getSize().x;
        item.icon.setScale(scale, scale);
        item.icon.setPosition(x + iconSize + columnSpacing, padding + visiblePotionIndex * (iconSize - 0));

        item.amountText.setFont(gameState.getContext().getResourceManager().getFont());
        item.updateText();

        potionIcons.push_back(std::move(item));

        ++visiblePotionIndex;
    }
}

void Player::initUI() {
    if (uiInitialized) return;
    uiInitialized = true;

    auto& font = gameState.getContext().getResourceManager().getFont();

    float x = gameState.getContext().getWindow().getSize().x - 250.f;
    float y = 10.f;
    float lineHeight = 25.f;

    statTexts.clear();
    for (int i = 0; i < 4; ++i) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(18);
        text.setFillColor(sf::Color::White);
        text.setPosition(x, y + i * lineHeight);
        statTexts.push_back(text);
    }

    float width = 200.f;
    float height = 20.f;
    float barY = y + 4 * lineHeight + 10.f;

    hpBarBack.setSize({ width, height });
    hpBarBack.setFillColor(sf::Color(80, 80, 80));
    hpBarBack.setPosition(x, barY);

    hpBarFront.setFillColor(sf::Color::Green);
    hpBarFront.setPosition(x, barY);

    updateUI();
    updateInventoryIcons();
}

void Player::handleInventoryClick(const sf::Vector2f& clickPosition) {
    for (auto& icon : weaponIcons) {
        if (icon.contains(clickPosition)) {
            if (icon.weapon != &equippedWeapon) {
                equipWeapon(*icon.weapon);
                updateUI();
                for (auto& w : weaponIcons)
                    w.selected = false;
                icon.selected = true;
            }
            return;
        }
    }

    for (auto& icon : potionIcons) {
        if (icon.icon.getGlobalBounds().contains(clickPosition)) {
            if (icon.potion && icon.potion->amount > 0) {
                switch (icon.potion->type) {
                case Potion::Type::Strength:
                    baseStats.strength += 2;
                    break;
                case Potion::Type::Defense:
                    baseStats.defense += 2;
                    break;
                case Potion::Type::Perception:
                    baseStats.perception += 2;
                    break;
                case Potion::Type::Intuition:
                    baseStats.intuition += 2;
                    break;
                case Potion::Type::Health:
                    baseStats.health = std::min(baseStats.maxHealth, baseStats.health + 25);
                    break;
                }

                const_cast<Potion*>(icon.potion)->amount--;

                icon.updateText();

                updateUI();
                updateInventoryIcons();
            }
            return;
        }
    }
}


void Player::updateUI() {
    if (statTexts.size() < 4) return;

    statTexts[0].setString("STR: " + std::to_string(getBaseStrength()) + " + " + std::to_string(getWeaponStrengthBonus()));
    statTexts[1].setString("DEF: " + std::to_string(getBaseDefense()) + " + " + std::to_string(getWeaponDefenseBonus()));
    statTexts[2].setString("INT: " + std::to_string(getBaseIntuition()) + " + " + std::to_string(getWeaponIntuitionBonus()));
    statTexts[3].setString("PER: " + std::to_string(getBasePerception()) + " + " + std::to_string(getWeaponPerceptionBonus()));

    float ratio = static_cast<float>(getCurrentHealth()) / getMaxHealth();
    float fullWidth = hpBarBack.getSize().x;
    hpBarFront.setSize({ fullWidth * ratio, hpBarBack.getSize().y });
}

void Player::render(sf::RenderWindow& window) {
    for (const auto& text : statTexts) window.draw(text);
    window.draw(hpBarBack);
    window.draw(hpBarFront);

    for (const auto& icon : weaponIcons)
        icon.draw(window);

    for (const auto& icon : potionIcons)
        icon.draw(window);
}

int Player::getBaseStrength() const { return baseStats.strength - equippedWeapon.attackBonus; }
int Player::getWeaponStrengthBonus() const { return equippedWeapon.attackBonus; }

int Player::getBaseDefense() const { return baseStats.defense - equippedWeapon.defenseBonus; }
int Player::getWeaponDefenseBonus() const { return equippedWeapon.defenseBonus; }

int Player::getBaseIntuition() const { return baseStats.intuition - equippedWeapon.intuitionBonus; }
int Player::getWeaponIntuitionBonus() const { return equippedWeapon.intuitionBonus; }

int Player::getBasePerception() const { return baseStats.perception - equippedWeapon.perceptionBonus; }
int Player::getWeaponPerceptionBonus() const { return equippedWeapon.perceptionBonus; }

int Player::getMaxHealth() const { return baseStats.maxHealth; }
int Player::getCurrentHealth() const { return baseStats.health; }
