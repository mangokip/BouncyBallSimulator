//
// Created by bryce-klein on 3/12/25.
//
#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class Sound {
public:
  bool loadSound(const std::string& name, const std::string& filepath);
  const sf::SoundBuffer& getSound(const std::string& name) const;
private:
  std::unordered_map<std::string, sf::SoundBuffer> sounds;
};
