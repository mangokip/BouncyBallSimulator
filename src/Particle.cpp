//
// Created by bryce-klein on 3/10/25
//
#include "Particle.hpp"
#include <cmath>

Particle::Particle(sf::Vector2f position, sf::Vector2f velocity, float lifetime)
    : velocity(velocity), lifetime(lifetime)
{
  shape.setRadius(2.0f);
  shape.setPosition(position);
  shape.setFillColor(sf::Color::Green);
  shape.setOrigin(2.0f, 2.0f);
}

void Particle::update(float dt) {
  shape.move(velocity * dt);
  lifetime -= dt;
  if (lifetime < 0.0f)
    lifetime = 0.0f;

  // fade out effect: adjust alpha based on remaining lifetime
  sf::Color col = shape.getFillColor();
  col.a = static_cast<sf::Uint8>(255 * (lifetime / 1.5f));
  shape.setFillColor(col);
}

void Particle::draw(sf::RenderWindow &window) {
  window.draw(shape);
}

bool Particle::isAlive() const {
  return lifetime > 0.0f;
}

void Particle::setColor(const sf::Color& color) {
  // set the color, preserving alpha if desired
  sf::Color newCol = color;
  newCol.a = shape.getFillColor().a;
  shape.setFillColor(newCol);
}
