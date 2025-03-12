//
// Created by bryce-klein on 3/8/25.
//
#include "Ball.hpp"
#include "Global.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp> // sf::Vector2f for 2d positions / velocity
#include<iostream>
#include<cstdlib> // std::rand();
#include"Sound.hpp"


// ----- ball constructor -----
// initializer: position parameter for where ball is on the window
Ball::Ball(sf::Vector2f position) {

  pos = position; //setting parameter

  // ------ set initial velocities using a smaller range -----
  // range: -0.25 to 0.25. If below a threshold, enforce a minimum speed.

  // notes: std::rand() % 101 gives int 0-100
  // -50 gives -50 to +50
  // dividing by 200.0f gives range of -0.25 to +0.25
  float speedX = (std::rand() % 101 - 50) / 200.0f;
  // adjusting global speed to carry over to each ball
  speedX *= globalSpeedMultiplier;
  // if abs speed is less than 0.15, then set it to +-0.15
  if (std::abs(speedX) < 0.15f) { speedX = (speedX >= 0) ? 0.15f : -0.15f; } // ensure a lower minimum

  float speedY = (std::rand() % 101 - 50) / 200.0f;
  speedY *= globalSpeedMultiplier;
  if (std::abs(speedY) < 0.15f) { speedY = (speedY >= 0) ? 0.15f : -0.15f; } // ensure a lower minimum

  vel = sf::Vector2f(speedX, speedY);
  baseVelocity = vel;

  // not necessary, but introducing random variations so not every ball is identical in movement
  vel.x += ((std::rand() % 10) - 5) * 0.01f;
  vel.y += ((std::rand() % 10) - 5) * 0.01f;

  float radius = std::max(5.0f, std::min((std::rand() % 26) + 5.0f, 30.0f)); // radius is 5 - 30
  circle.setRadius(radius); // SFML - setRadius defines a CircleShape size
  circle.setPosition(pos); // SFML - setPosition defines starting position for CircleShape

  //making gravity extremely weak to avoid balls stopping too fast
  gravity = 0.001f;


  //just wanted random color
  sf::Color randomColor(
    std::rand() % 256,
    std::rand() % 256,
    std::rand() % 256
  );
  circle.setFillColor(randomColor); // SFML - setFillColor is for determining the color to fill the CircleShape with

  //sanity check to avoid core dump on radius
  if (radius <= 0) radius = 10;

  //centering the circle instead of having the ball spawn at the top left corner of shape
  circle.setOrigin(radius, radius);
}

/* update ball's position and velocity + other factors
   using a reference for sf::RenderWindow& to pass "window" by reference. The window won't be needlessly copied and can
   be modified directly.
   side note: SFML requires this, copies of sf::RenderWindow are not allowed */
void Ball::update(sf::RenderWindow& window, bool gravityEnabled) {

  // pos: current position
  // vel: movement per frame
  // new position = old position + velocity
  pos += vel; // moving ball based on velocity, e.g, if vel.x = 1.5 then the ball moves 1.5 pixels a frame
  circle.setPosition(pos);
  // ball will not move too fast upwards and vel.y is needed since gravity is downward acceleration
  if (gravityEnabled) {
    vel.y += gravity * globalGravity;
  }

  // variables to implement wall collision
  float winWidth = window.getSize().x;
  float winHeight = window.getSize().y;
  float radius = circle.getRadius();


  // ----- left wall collision -----
  // if center of ball - radius is beyond 0, then it's out of bounds
  if (pos.x - radius < 0) {
    spawnParticles(sf::Vector2f(pos.x, pos.y), 10, 0.0f, 1.57f); // spawn particles in a crescent from 0 to PI/2 (0 to 90°)
    float randomPitch = 0.3f + static_cast<float>(std::rand()) / RAND_MAX * (3.0f - 0.3f);
    collisionSound.setPitch(randomPitch);
    collisionSound.play();
    vel.x = -vel.x; // reverse velocity to bounce in opposite direction
    pos.x = radius; // ball is touching left wall exactly
  }
  // ----- right wall collision -----
  if (pos.x + radius > winWidth) {

    spawnParticles(sf::Vector2f(pos.x, pos.y), 10, 3.14f, 4.71f); // spawn particles in a crescent from PI to 3*PI/2 (180° to 270°)
    float randomPitch = 0.3f + static_cast<float>(std::rand()) / RAND_MAX * (3.0f - 0.3f);
    collisionSound.setPitch(randomPitch);
    collisionSound.play();
    vel.x = -vel.x;
    pos.x = winWidth - radius;
  }

  // ----- floor collision -----
  if (pos.y + radius > winHeight) {
    spawnParticles(sf::Vector2f(pos.x, pos.y), 10, 4.71f, 6.28f);
    float randomPitch = 0.3f + static_cast<float>(std::rand()) / RAND_MAX * (3.0f - 0.3f);
    collisionSound.setPitch(randomPitch);
    collisionSound.play();
    if (gravityEnabled && globalGravity >= 100.0f) {
      vel.y = 0.0f;
      vel.x *= 0.90f;
    } else if (gravityEnabled) {
      vel.y = -vel.y * 0.98f;
      vel.x *= 0.995f;
    } else {
      vel.y = -vel.y;
    }
    pos.y = winHeight - radius;
  }


  // ----- ceiling collision -----
  if (pos.y - radius < 0) {
    float randomPitch = 0.3f + static_cast<float>(std::rand()) / RAND_MAX * (3.0f - 0.3f);
    collisionSound.setPitch(randomPitch);
    collisionSound.play();
    spawnParticles(sf::Vector2f(pos.x, pos.y), 10, 1.57f, 3.14f); // spawn particles downward: e.g., from 1.57 to 3.14 radians (90° to 180°)
    vel.y = -vel.y;
    pos.y = radius;
  }

  circle.setPosition(pos);
}

// basic function to draw to the window
void Ball::draw(sf::RenderWindow& window) {
  window.draw(circle);
}