#include "Global.hpp"
#include "Particle.hpp"
#include <cstdlib>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Sound.hpp"
#include <iostream>

float globalSpeedMultiplier = 1.0f;
std::vector<Particle> particles;

Sound sound;
std::vector<sf::Sound> sounds;
sf::Sound buttonSound;
sf::Sound spawnSound;
sf::Sound collisionSound;

void spawnParticles(sf::Vector2f position, int count, float angleStart, float angleEnd) {
  const size_t MAX_PARTICLES = 1000;  // set an upper limit
  // remove the oldest particles if needed
  while (particles.size() + count > MAX_PARTICLES) {
    particles.erase(particles.begin());
  }
  for (int i = 0; i < count; i++) {
    float angle = angleStart + static_cast<float>(std::rand()) / RAND_MAX * (angleEnd - angleStart);
    float speed = (std::rand() % 50) / 100.0f + 0.1f;
    sf::Vector2f pVel(std::cos(angle) * speed, std::sin(angle) * speed);

    // generate a random offset to spread the particles out
    float offsetMagnitude = static_cast<float>(std::rand() % 51) / 10.0f; // 0 to 5 pixels
    float offsetAngle = static_cast<float>(std::rand()) / RAND_MAX * 2 * 3.14159f;
    sf::Vector2f offset(std::cos(offsetAngle) * offsetMagnitude, std::sin(offsetAngle) * offsetMagnitude);

    // random color for each particle
    sf::Color randomColor(
        std::rand() % 256,
        std::rand() % 256,
        std::rand() % 256
    );

    Particle p(position + offset, pVel, 1.5f);
    p.setColor(randomColor);
    particles.push_back(p);
  }
}


