#include "Global.hpp"
#include "Particle.hpp"
#include <cstdlib>
#include <cmath>
#include <SFML/Graphics.hpp>

float globalSpeedMultiplier = 1.0f;
std::vector<Particle> particles;

void spawnParticles(sf::Vector2f position, int count, float angleStart, float angleEnd) {

  for (int i = 0; i < count; i++) {
    // generate a random emission angle within [angleStart, angleEnd]
    float angle = angleStart + static_cast<float>(std::rand()) / RAND_MAX * (angleEnd - angleStart);
    // random speed between 0.1 and 0.5
    float speed = (std::rand() % 50) / 100.0f + 0.1f;
    sf::Vector2f vel(std::cos(angle) * speed, std::sin(angle) * speed);

    // generate a random offset to spread the particles out:
    // this offset is chosen by generating a random magnitude (e.g., up to 5 pixels) and a random angle (0 to 2π).
    float offsetMagnitude = static_cast<float>(std::rand() % 51) / 10.0f; // 0 to 5.0 pixels
    float offsetAngle = static_cast<float>(std::rand()) / RAND_MAX * 2 * 3.14159f;
    sf::Vector2f offset(std::cos(offsetAngle) * offsetMagnitude, std::sin(offsetAngle) * offsetMagnitude);

    // generate a random color for the particle.
    sf::Color randomColor(
        std::rand() % 256,
        std::rand() % 256,
        std::rand() % 256
    );

    Particle p(position + offset, vel, 1.5f);
    p.setColor(randomColor);
    particles.push_back(p);
  }
}
