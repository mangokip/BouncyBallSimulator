//
// Created by bryce-klein on 3/10/25
//
#include "Particle.hpp"
#include <cmath> // std::cos and sin

/* basic notes for myself: Particles are created on the heap in a vector.
   sf::CircleShape allocates its own memory by SFML

   formulas used: distance = speed * time
                  alpha = 255 * (lifetime / 1.5f)
   particles are dynamically allocated saving space
*/
// ----- constructor -----
// lifetime = how long i want the particle to live
// initializer in declaration is to initialize member variables velocity and lifetime
// with the given parameters
/*
 * WHY? initializer lists are useful for saving a tiny bit of memory instead of default constructing
 */
Particle::Particle(sf::Vector2f position, sf::Vector2f velocity, float lifetime)
    : velocity(velocity), lifetime(lifetime)
{
  shape.setRadius(2.0f);
  shape.setPosition(position);
  shape.setFillColor(sf::Color::Green);
  shape.setOrigin(2.0f, 2.0f);
}

// ----- updating particle display -----
// dt = delta time = time elapsed since last update (in seconds)
void Particle::update(float dt) {
  shape.move(velocity * dt); // distance = velocity * time, effectively moving particle by this offset
  lifetime -= dt; // subtracting elapsed time from remaining life
  if (lifetime < 0.0f) // no negatives allowed duh
    lifetime = 0.0f;

  // fade out effect: adjust alpha based on remaining lifetime
  sf::Color col = shape.getFillColor(); // determines current color
  // multiplying this relativity by 255 gives a 0-255 alpha range
  // it is being statically cast to an 8bit unsigned int for color components
  // as lifetime decrements, the alpha value decreases causing it to fade
  // basically linear interpolation of transparency in laymens terms but not really
  col.a = static_cast<sf::Uint8>(255 * (lifetime / 1.5f)); // relativity = lifetime relative to initial lifetime

  shape.setFillColor(col);
}

// ----- draw particle -----
void Particle::draw(sf::RenderWindow &window) {
  window.draw(shape);
}

// ----- life check ------
bool Particle::isAlive() const {
  return lifetime > 0.0f;
}

void Particle::setColor(const sf::Color& color) {
  // set the color, preserving alpha if desired
  sf::Color newCol = color;
  newCol.a = shape.getFillColor().a;
  shape.setFillColor(newCol);
}
