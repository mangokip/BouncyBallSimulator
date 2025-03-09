#include "Ball.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include<iostream>
#include<cstdlib>
#include<ctime>

Ball::Ball(sf::Vector2f position) {
  pos = position;

  float speedX = (std::rand() % 41 - 20) / 10.0f;
  float speedY = (std::rand() % 61 - 30) / 10.0f;
  vel = sf::Vector2f(speedX, speedY);


  float radius = std::max(5.0f, std::min((std::rand() % 26) + 5.0f, 30.0f));
  circle.setRadius(radius);
  circle.setPosition(pos);

  gravity = (std::rand() % 4 + 1) / 10000.0f;




  sf::Color randomColor(
    std::rand() % 256,
    std::rand() % 256,
    std::rand() % 256
  );
  circle.setFillColor(randomColor);
  if (radius <= 0) radius = 10;
  circle.setOrigin(radius, radius);
}

void Ball::update(sf::RenderWindow& window) {
  const float maxSpeed = 5.0f;
  const float friction = 0.98f;
  const float airFriction = 0.999f;


  pos += vel;
  if (vel.y > -maxSpeed) {
    vel.y += gravity;
  }

  vel.x *= airFriction;
  if (std::abs(vel.x) < 0.05f) vel.x = 0.0f;

  if (vel.y > maxSpeed) vel.y = maxSpeed;
  if (vel.y < -maxSpeed) vel.y = -maxSpeed;

  float winWidth = window.getSize().x;
  float winHeight = window.getSize().y;

  float radius = circle.getRadius();

  if (pos.x - radius < 0 || pos.x + radius > winWidth) {
    vel.x = -vel.x * 0.99f;
    pos.x = std::max(radius, std::min(pos.x, winWidth - radius));
  }

  if (pos.y + radius > winHeight) {
    vel.y = -vel.y * 0.96f; // Lose energy on bounce
    pos.y = winHeight - radius;

    vel.x *= friction;
  }

  if (pos.y - radius < 0) {
    vel.y = -vel.y * 0.99f;
    pos.y = radius;
  }


  circle.setPosition(pos);
}

void Ball::draw(sf::RenderWindow &window) {
  window.draw(circle);
}