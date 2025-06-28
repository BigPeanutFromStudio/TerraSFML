#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Player {
public:
  Player(const sf::Sprite &sprite);
  void draw(sf::RenderWindow &window);
  void update(const int delta_time);
  void set_position(const sf::Vector2f &position);
  sf::Vector2f get_position();
  void set_acceleration(const float &x_acceleration);

private:
  sf::Sprite _sprite;
  sf::Vector2f _velocity;
  sf::Vector2f _acceleration;
  void accelerate_x();
};
