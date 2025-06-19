#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <iostream>

class AssetManager
{
public:
    void loadTexture(const std::string &name, const std::string &filepath);
    sf::Texture &getTexture(const std::string &name);

private:
    std::unordered_map<std::string, sf::Texture> textures;
};