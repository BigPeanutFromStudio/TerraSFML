#pragma once

#include <SFML/Graphics.hpp>

class Player {
public:
  Player(const sf::Sprite &sprite);
  void draw(sf::RenderWindow &window);
  void update(const int delta_time);
  void set_position(const sf::Vector2f &position);
  sf::Vector2f get_position() const;
  void set_acceleration(const float &x_acceleration);
  // These could be probably better names
  void check_vertical_collisions(const sf::Sprite &other);
  void check_horizontal_collisons(const sf::Sprite &other);

private:
  sf::Sprite _sprite;
  sf::Vector2f _velocity;
  sf::Vector2f _acceleration;
  float _friction;
  void accelerate_x();
};
