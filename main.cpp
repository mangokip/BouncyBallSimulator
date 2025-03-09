#include "Ball.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

#include <memory>

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed randomness once

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    std::vector<std::unique_ptr<Ball>> balls;


    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event)) // pollEvent needs an event reference
        {
            if (event.type == sf::Event::Closed) // Check event type properly
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f clickPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                balls.push_back(std::make_unique<Ball>(clickPos)); // Store a pointer to a ball
            }

        }

        window.clear();
        for (auto& ball : balls) {
           ball->update(window);
            ball->draw(window);
        }
        window.display();

    }

    return 0;
}

