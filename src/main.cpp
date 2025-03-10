#include "Ball.hpp"
#include "Global.hpp"
#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

#include <memory>

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr))); // seed randomness once

    // ----- window setup + ball setup -----
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Ball Simulator");
    std::vector<std::unique_ptr<Ball>> balls; // need unique_ptr to avoid memory leaks, if out of scope then delete

    // ----- gravity button -----
    Button gravityButton(50, 50, 240, 70, "Toggle Gravity");  // Move it more to the left
    bool gravityEnabled = true;

    // ------ clear button -----
    Button clearButton(50,150,200, 70, "Clear Balls");

    // ----- increase speed button -----
    Button increaseSpeedButton(50,250, 270, 70, "Increase Speed");

    // ----- decrease speed button -----
    Button decreaseSpeedButton(50,350,270,70, "Decrease Speed");

    // ----- particle clock -----
    sf::Clock clock;

    // ----- main loop for when window is open -----
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


                bool buttonClicked = false;
                // ----- toggle gravity button check -----
                if (gravityButton.isClicked(clickPos)) {
                    gravityEnabled = !gravityEnabled;
                    buttonClicked = true;
                }
                // ----- clear ball button check-----
                if (clearButton.isClicked(clickPos)) {
                    balls.clear();
                    buttonClicked = true;
                }

                // ----- increase speed button check -----
                if (increaseSpeedButton.isClicked(clickPos)) {
                    globalSpeedMultiplier *= 1.1f;
                    std::cout << "globalSpeedMultiplier = " << globalSpeedMultiplier << std::endl;

                    for (auto &ball : balls) {
                        ball->setVelocity(ball->getVelocity() * 1.1f);
                    }
                    buttonClicked = true;
                }

                // ----- decrease speed button check -----
                if (decreaseSpeedButton.isClicked(clickPos)) {
                    globalSpeedMultiplier *= 0.9f;
                    std::cout << "globalSpeedMultiplier = " << globalSpeedMultiplier << std::endl;

                    for (auto &ball : balls) {
                        ball->setVelocity(ball->getVelocity() * 0.9f);
                    }
                    buttonClicked = true;
                }

                // ----- general screen click -----
                if (!buttonClicked) {
                    balls.push_back(std::make_unique<Ball>(clickPos));
                }


            }

        }

        // mapping cords to apply hover effect
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        gravityButton.setHoverEffect(mousePos);
        clearButton.setHoverEffect(mousePos);
        increaseSpeedButton.setHoverEffect(mousePos);
        decreaseSpeedButton.setHoverEffect(mousePos);

        // ----- update particles -----
        float dt = clock.restart().asSeconds();
        for (auto it = particles.begin(); it != particles.end(); ) {
            it->update(dt);
            if (!it->isAlive()) {
                it = particles.erase(it);
            } else {
                ++it;
            }
        }

        for (auto& ball : balls) {
            ball->update(window, gravityEnabled);
        }

        window.clear(); // removing previous frame to avoid ghost effects
        // auto& ball -> reference to each element in "balls" vector
        // not using Ball* ball : balls because balls stores a unique pointer and
        // not raw ball pointers.
        for (auto& ball : balls) {
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

        for (auto& particle : particles) {
            particle.draw(window);
        }
        gravityButton.draw(window);
        clearButton.draw(window);
        increaseSpeedButton.draw(window);
        decreaseSpeedButton.draw(window);

        window.display(); // updates rendered frame from above

    }

    return 0;
}

