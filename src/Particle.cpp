//
// Created by bryce-klein on 3/10/25.
//
#include "Particle.hpp"
#include <cmath>

Particle::Particle(sf::Vector2f position, sf::Vector2f velocity, float lifetime) : velocity(velocity), lifetime(lifetime) {
    shape.setRadius(2.0f);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(2.0f, 2.0f);
}

void Particle::update(float dt) {
    shape.move(velocity * dt);
    lifetime -= dt;
    if (lifetime < 0.0f) {
      lifetime = 0.0f;
    }

    sf::Color color = shape.getFillColor();
    color.a = static_cast<sf::Uint8>(255 * (lifetime / 1.5f));
    shape.setFillColor(color);
}

void Particle::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

bool Particle::isAlive() const {
  return lifetime > 0.0f;
}

void Particle::setColor(const sf::Color& color) {
  sf::Color col = shape.getFillColor();
  col = color; // set the new color (optionally, keep the alpha the same)
  shape.setFillColor(col);
}
