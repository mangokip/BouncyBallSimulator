//
// Created by bryce-klein on 3/9/25.
//

#ifndef BALL_HPP
#define BALL_HPP
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdlib>

class Ball {
public:
  explicit Ball(sf::Vector2f position);

  sf::Vector2f getVelocity() const { return vel; }
  void setVelocity(const sf::Vector2f &newVel) { vel = newVel; }
  void update(sf::RenderWindow& window, bool gravityEnabled);
  void draw(sf::RenderWindow& window);

private:
  sf::Vector2f pos{};
  sf::Vector2f vel{};
  float gravity;
  sf::CircleShape circle{};
};

#endif //BALL_HPP
