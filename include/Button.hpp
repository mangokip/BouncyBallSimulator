//
// Created by bryce-klein on 3/10/25.
//

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include<SFML/Graphics.hpp>
class Button {
  public:
    Button(float x, float y, float width, float height, const std::string& text);

    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Vector2f mousePosition);
    void setHoverEffect(sf::Vector2f hoverPosition);

  private:
     sf::RectangleShape shape;
     sf::Text buttonText;
     sf::Font buttonFont;
};


#endif //BUTTON_HPP
