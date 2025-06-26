#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Player {
public:
  Player(const sf::Sprite &sprite);
  void draw(sf::RenderWindow &window);
  void update(const int delta_time);
  void set_position(const sf::Vector2f &position);
  void apply_velocity(const sf::Vector2f &velocity);
  void add_velocity(const sf::Vector2f &velocity);

private:
  sf::Sprite _sprite;
  sf::Vector2f _velocity;
};
