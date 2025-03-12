//
// Created by bryce-klein on 3/12/25.
//
#include "Sound.hpp"
#include <iostream>

bool Sound::loadSound(const std::string& name, const std::string& filepath) {
  sf::SoundBuffer buffer;
  if (!buffer.loadFromFile(filepath)) {
    std::cerr << "Failed to load sound: " << filepath << std::endl;
    return false;
  }
  sounds[name] = buffer;
  return true;
}

const sf::SoundBuffer& Sound::getSound(const std::string& name) const {
  return sounds.at(name);
}
