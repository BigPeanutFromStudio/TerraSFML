#include <Player.h>
#include <SFML/System/Vector2.hpp>
#include <algorithm>

// TODO: Add acceleration, friction, gravity, jumping and collisions

Player::Player(const sf::Sprite &sprite) : _sprite(sprite) {}

void Player::draw(sf::RenderWindow &window) { window.draw(_sprite); }

void Player::set_position(const sf::Vector2f &position) {
  _sprite.setPosition(position);
}

sf::Vector2f Player::get_position() { return _sprite.getPosition(); }

void Player::set_acceleration(const float &x_acceleration) {
  _acceleration.x = x_acceleration;
}

void Player::accelerate_x() {
  _velocity.x += _acceleration.x;
  const float x_vel = std::clamp(_velocity.x, -0.5f, 0.5f);
  _velocity.x = x_vel;
}

void Player::update(const int delta_time) {
  accelerate_x();
  // Apply friction - TODO: define a _friction variable
  _velocity.x *= 0.9f;
  _sprite.move(_velocity * (float)delta_time);
}
