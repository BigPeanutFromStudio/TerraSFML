#include <Player.h>
#include <algorithm>

// TODO: Add gravity, jumping and collisions

Player::Player(const sf::Sprite &sprite) : _sprite(sprite) { _friction = 0.9f; }

void Player::draw(sf::RenderWindow &window) { window.draw(_sprite); }

void Player::set_position(const sf::Vector2f &position) {
  _sprite.setPosition(position);
}

sf::Vector2f Player::get_position() const { return _sprite.getPosition(); }

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
  _velocity.x *= _friction;
  _sprite.move(_velocity * (float)delta_time);
}

void Player::check_horizontal_collisons(const sf::Sprite &other) {
  if (_sprite.getGlobalBounds().findIntersection(other.getGlobalBounds())) {
    if (_velocity.x < 0) {
      sf::Vector2f newPos = _sprite.getPosition();
      newPos.x = other.getPosition().x + other.getGlobalBounds().size.x;
      _sprite.setPosition(newPos);
      _velocity.x = 0;
      _acceleration.x = 0;
    } else if (_velocity.x > 0) {
      sf::Vector2f newPos = _sprite.getPosition();
      newPos.x = other.getPosition().x - _sprite.getGlobalBounds().size.x;

      _sprite.setPosition(newPos);
      _velocity.x = 0;
      _acceleration.x = 0;
    }
  }
}

void Player::check_vertical_collisions(const sf::Sprite &other) {
  if (_velocity.y < 0 && other.getPosition().y > _sprite.getPosition().y) {
    sf::Vector2f newPos = other.getPosition();
    newPos.x = _sprite.getPosition().x;
    _sprite.setPosition(newPos);
    _velocity.y = 0;
    _acceleration.y = 0;
  } else if (_velocity.y > 0 &&
             other.getPosition().y < _sprite.getPosition().y) {
    sf::Vector2f newPos = other.getPosition();
    newPos.x = _sprite.getPosition().x;
    _sprite.setPosition(newPos);
    _velocity.y = 0;
    _acceleration.y = 0;
  }
}
