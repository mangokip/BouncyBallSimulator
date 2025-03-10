//
// Created by bryce-klein on 3/10/25.
//
#include "Button.hpp"
#include<iostream>

// ----- constructor -----
Button::Button(float x, float y, float width, float height, const std::string& text) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);

    // default font
    if (!buttonFont.loadFromFile("assets/fonts/OpenSans-VariableFont_wdth,wght.ttf")) {
      throw std::runtime_error("failed to load font");
    }

    buttonText.setFont(buttonFont);
    buttonText.setString(text);
    buttonText.setCharacterSize(30);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(x + 20, y + 10);

    // console check for button creation
    std::cout << "Button Bounds: Left=" << shape.getGlobalBounds().left
        << " Top=" << shape.getGlobalBounds().top
        << " Width=" << shape.getGlobalBounds().width
        << " Height=" << shape.getGlobalBounds().height << std::endl;

}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(buttonText);
}

void Button::setHoverEffect(sf::Vector2f mousePosition) {
    if(shape.getGlobalBounds().contains(mousePosition)) {
      shape.setFillColor(sf::Color::Red);
    } else {
      shape.setFillColor(sf::Color::White);
    }
}

bool Button::isClicked(sf::Vector2f mousePosition) {
  return shape.getGlobalBounds().contains(mousePosition);
}
