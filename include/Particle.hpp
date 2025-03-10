//
// Created by bryce-klein on 3/10/25.
//

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

class Particle {
  public:
    Particle(sf::Vector2f position, sf::Vector2f velocity, float lifetime);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isAlive() const;
    void setColor(const sf::Color& color);

   private:
     sf::CircleShape shape;
     sf::Vector2f velocity;
     float lifetime;
};

#endif //PARTICLE_HPP
