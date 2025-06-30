#include <InputManager.h>

InputManager::InputManager() { _initBinds(); }

void InputManager::_initBinds() {
  _keybinds[Action::MoveLeft] = sf::Keyboard::Key::A;
  _keybinds[Action::MoveRight] = sf::Keyboard::Key::D;
  _keybinds[Action::Jump] = sf::Keyboard::Key::Space;
}

void InputManager::resetFrameState() {
  for (auto &[action, state] : _eventStates) {
    state = false;
  }
}

void InputManager::update() {

  for (const auto &[action, key] : _keybinds) {
    _heldStates[action] = sf::Keyboard::isKeyPressed(key);
  }
}

void InputManager::handleEvent(const sf::Event &event) {
  if (auto keyEvent = event.getIf<sf::Event::KeyPressed>()) {
    for (const auto &[action, key] : _keybinds) {
      _eventStates[action] = keyEvent->code == key;
    }
  }
}

bool InputManager::isActionHeld(Action action) const {
  auto it = _heldStates.find(action);
  return it != _heldStates.end() && it->second;
}

bool InputManager::isActionPressed(Action action) const {
  auto it = _eventStates.find(action);
  return it != _eventStates.end() && it->second;
}
