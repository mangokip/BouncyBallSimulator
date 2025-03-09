#include "Ball.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp> //sf::Vector2f for 2d positions / velocity

#include<iostream>
#include<cstdlib> // std::rand();

// ball constructor
// initializer: position parameter for where ball is on the window
Ball::Ball(sf::Vector2f position) {
  pos = position; //setting parameter

  // random velocities in a set range
  float speedX = (std::rand() % 41 - 20) / 10.0f; // -2 to 2
  float speedY = (std::rand() % 61 - 30) / 10.0f; // -3 to 3
  vel = sf::Vector2f(speedX, speedY); //float vector


  float radius = std::max(5.0f, std::min((std::rand() % 26) + 5.0f, 30.0f)); // radius is 5 - 30
  circle.setRadius(radius); // SFML - setRadius defines a CircleShape size
  circle.setPosition(pos); // SFML - setPosition defines starting position for CircleShape

  //making gravity extremely weak to avoid balls stopping too fast
  gravity = (std::rand() % 4 + 1) / 10000.0f; // 0.0001 to 0.0004



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
void Ball::update(sf::RenderWindow& window) {
  const float maxSpeed = 5.0f; // to prevent speed from getting too fast, this is already a generous value
  const float friction = 0.98f; // very low friction
  const float airFriction = 0.999f; // even lower "friction" to slow down horizontal speed


  // pos: current position
  // vel: movement per frame
  pos += vel; // moving ball based on velocity, e.g, if vel.x = 1.5 then the ball moves 1.5 pixels a frame

  // ball will not move too fast upwards and vel.y is needed since gravity is downward acceleration
  if (vel.y > -maxSpeed) {
    vel.y += gravity;
  }

  // to halt horizontal motion over time
  vel.x *= airFriction;
  if (std::abs(vel.x) < 0.05f) vel.x = 0.0f; // this just stops balls that are extremely close to stopping

  if (vel.y > maxSpeed) vel.y = maxSpeed;
  if (vel.y < -maxSpeed) vel.y = -maxSpeed;

  // variables to implement wall collision
  float winWidth = window.getSize().x;
  float winHeight = window.getSize().y;
  float radius = circle.getRadius();

  // checking horizontal collision
  if (pos.x - radius < 0 || pos.x + radius > winWidth) {
    vel.x = -vel.x * 0.99f;
    //resetting position if out of bounds to properly implement collision
    pos.x = std::max(radius, std::min(pos.x, winWidth - radius));
  }

  // floor collision
  if (pos.y + radius > winHeight) {
    vel.y = -vel.y * 0.96f; // flip velocity upwards if past bottom of window and reduces energy
    pos.y = winHeight - radius;

    vel.x *= friction; // extra friction if at bottom
  }

  // ceiling collision
  if (pos.y - radius < 0) {
    vel.y = -vel.y * 0.99f;
    pos.y = radius;
  }

  circle.setPosition(pos);
}

// basic function to draw to the window
void Ball::draw(sf::RenderWindow& window) {
  window.draw(circle);
}