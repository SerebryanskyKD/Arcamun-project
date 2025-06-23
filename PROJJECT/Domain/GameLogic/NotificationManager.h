#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct Notification {
    std::string text;
    sf::Text sfText;
    float timeRemaining;

    Notification(const std::string& msg, const sf::Font& font, float duration, sf::Vector2f position) : text(msg), timeRemaining(duration)
    {
        sfText.setFont(font);
        sfText.setString(msg);
        sfText.setCharacterSize(36);
        sfText.setFillColor(sf::Color::Red);
        sf::FloatRect bounds = sfText.getLocalBounds();
        sfText.setOrigin(bounds.width / 2, bounds.height / 2);
        sfText.setPosition(position);
    }
};

class NotificationManager {
public:
    NotificationManager(const sf::Font& font, sf::Vector2f windowCenterTop) : font(font), position(windowCenterTop) {}

    void add(const std::string& message, float duration = 1.0f) {
        notifications.emplace_back(message, font, duration, position);
    }

    void update(float deltaTime) {
        for (auto& notif : notifications)
            notif.timeRemaining -= deltaTime;

        notifications.erase(
            std::remove_if(notifications.begin(), notifications.end(), [](const Notification& n) { return n.timeRemaining <= 0; }),
            notifications.end());
    }

    void render(sf::RenderWindow& window) {
        for (const auto& notif : notifications)
            window.draw(notif.sfText);
    }

private:
    const sf::Font& font;
    sf::Vector2f position;
    std::vector<Notification> notifications;
};
