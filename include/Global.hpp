#pragma once
#include <vector>
#include "Particle.hpp"

extern float globalSpeedMultiplier;
extern std::vector<Particle> particles;

// declaration with default arguments
void spawnParticles(sf::Vector2f position, int count = 20, float angleStart = 0.785f, float angleEnd = 2.356f);
