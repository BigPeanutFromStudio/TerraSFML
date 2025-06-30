#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

enum class Action { MoveRight, MoveLeft, Jump };

class InputManager {
public:
  InputManager();
  bool isActionHeld(Action action) const;
  bool isActionPressed(Action action) const;
  void update();
  void handleEvent(const sf::Event &event);
  void resetFrameState();

private:
  std::unordered_map<Action, sf::Keyboard::Key> _keybinds;
  std::unordered_map<Action, bool> _heldStates;
  std::unordered_map<Action, bool> _eventStates;
  void _initBinds();
};
