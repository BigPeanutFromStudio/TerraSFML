#include <AssetManager.h>
#include <iostream>

void AssetManager::loadTexture(const std::string &name,
                               const std::string &filepath) {
  sf::Texture texture;
  if (!texture.loadFromFile(filepath)) {
    std::cerr << "Failed to load texture: " << filepath << std::endl;
  }
  textures[name] = texture;
}

const sf::Texture &AssetManager::getTexture(const std::string &name) const {
  return textures.at(name);
}
