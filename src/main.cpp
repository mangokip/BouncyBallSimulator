#include "Ball.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

#include <memory>

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr))); // seed randomness once

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    std::vector<std::unique_ptr<Ball>> balls; // need unique_ptr to avoid memory leaks, if out of scope then delete


    while (window.isOpen())
    {
        sf::Event event{}; // SFML will queue various computer events
        while (window.pollEvent(event)) // pollEvent needs an event reference
        {
            if (event.type == sf::Event::Closed) // close window if event is "Closed"
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                // sf::Mouse::getPosition(window) - grabbing pixel coords of mouse
                // window.mapPixelToCoords - pixels -> world coordinate
                // std::make_unique<Type = Ball>(clickPos) - new ball at mouse position
                // push_back increases vector size for new ball
                sf::Vector2f clickPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                balls.push_back(std::make_unique<Ball>(clickPos)); // Store a pointer to a ball
            }

        }

        window.clear(); // removing previous frame to avoid ghost effects
        // auto& ball -> reference to each element in "balls" vector
        // not using Ball* ball : balls because balls stores a unique pointer and
        // not raw ball pointers.
        for (auto& ball : balls) {
           ball->update(window); // calls Ball::update(sf::RenderWindow&) to update ball qualities
            ball->draw(window); // calls Ball::draw(sf::RenderWindow&) after
            /* note for myself: balls is a std::vector<std::unique_ptr<Ball>> so it stores smart pointers
             * meaning each ball is a std::unique_ptr<Ball> and not an actual Ball object
             * -> dereferences the smart pointer to access methods of Ball.
             *
             * WHY? Balls are dynamically allocated instead of having regular objects.
             *
             * NO POINTERS:
             * if I didn't use pointers, a Ball object would be temp made, copied into vector,
             * and then destroyed. If the vector grows, all of the Ball objects will need to be
             * copied into another location in memory.
             *
             * More copies = more CPU cycles and more growth = new memory
             * We don't have as much freedom over creation / deletion
             *
             * POINTERS:
             * Ball is created on the heap and not the stack, and a std::unique_ptr<Ball> is returned
             * push_back will now move the unique pointer into the vector without copying the ball
             * The vector is a list of pointers instead of objects
             * unique pointers also auto manage their memory. Balls being removed frees memory
             *
             */
        }
        window.display(); // updates rendered frame from above

    }

    return 0;
}

