#include <Player.h>
#include <SFML/System/Vector2.hpp>

Player::Player(const sf::Sprite &sprite) : _sprite(sprite) {}

void Player::draw(sf::RenderWindow &window) { window.draw(_sprite); }

void Player::set_position(const sf::Vector2f &position) { _sprite.setPosition(position); }

void Player::apply_velocity(const sf::Vector2f &velocity) {
    _velocity = velocity;
}

void Player::add_velocity(const sf::Vector2f &velocity){
    _velocity += velocity;
}

void Player::update(const int delta_time){
    _sprite.move(_velocity * (float)delta_time);
} 
