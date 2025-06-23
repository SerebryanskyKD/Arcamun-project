#pragma once
#include <string>
#include <SFML/Graphics.hpp>

struct InventoryItem {
    virtual bool isWeapon() const = 0;
    virtual ~InventoryItem() = default;
};

struct Weapon : public InventoryItem {
    Weapon() = default;

    enum class Type {
        SwordAndShield,
        Staff,
        EnchantedStaff
    };
    
    bool isWeapon() const override { 
        return true;
    }

    Type type;
    std::string name;
    int attackBonus, defenseBonus, intuitionBonus, perceptionBonus;
    sf::Texture* texture = nullptr;

    Weapon(Type type, const std::string& name, int atk, int def, int intu, int perc, sf::Texture* texture = nullptr)
        : type(type), name(name), attackBonus(atk), defenseBonus(def), intuitionBonus(intu), perceptionBonus(perc), texture(texture) {
    }
};

inline Weapon::Type weaponTypeFromString(const std::string& typeStr) {

    if (typeStr == "SwordAndShield") return Weapon::Type::SwordAndShield;
    if (typeStr == "Staff") return Weapon::Type::Staff;
    if (typeStr == "EnchantedStaff") return Weapon::Type::EnchantedStaff;
    throw std::invalid_argument("Unknown Weapon Type: " + typeStr);
}

struct Potion : public InventoryItem {
    enum class Type {
        Strength,
        Defense,
        Perception,
        Intuition,
        Health
    };

    bool isWeapon() const override {
        return false;
    }

    Type type;
    std::string name;
    int amount = 0;
    sf::Texture* texture = nullptr;

    Potion(Type type, const std::string& name, int amount = 1, sf::Texture* texture = nullptr)
        : type(type), name(name), amount(amount), texture(texture) {
    }
};
