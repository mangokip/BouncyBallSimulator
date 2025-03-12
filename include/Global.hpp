//
// Created by bryce-klein on 3/10/25
//
#pragma once
#include <vector>
#include "Particle.hpp"
#include "Sound.hpp"

extern float globalSpeedMultiplier;
extern std::vector<Particle> particles;
extern Sound sound;
extern std::vector<sf::Sound> sounds;
extern sf::Sound collisionSound;
extern sf::Sound spawnSound;
extern sf::Sound buttonSound;
extern float globalGravity;


// default
void spawnParticles(sf::Vector2f position, int count = 20, float angleStart = 0.785f, float angleEnd = 2.356f);
