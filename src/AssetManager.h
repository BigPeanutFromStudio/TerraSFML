#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class AssetManager {
public:
  void loadTexture(const std::string &name, const std::string &filepath);
  const sf::Texture &getTexture(const std::string &name) const;

private:
  std::unordered_map<std::string, sf::Texture> textures;
};
