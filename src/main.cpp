#include <AssetManager.h>
#include <InputManager.h>
#include <Player.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

void loadAssets(AssetManager &assetManager) {
  assetManager.loadTexture("grass", "./assets/grass.png");
  assetManager.loadTexture("dirt", "./assets/dirt.png");
  assetManager.loadTexture("player", "./assets/player.png");
}

void drawGroup(sf::RenderWindow &window, const std::vector<sf::Sprite> &group) {
  for (sf::Sprite sprite : group) {
    window.draw(sprite);
  }
}

int main() {

  const int WINDOW_WIDTH = 1280;
  const int WINDOW_HEIGHT = 720;

  auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                                 "TerraSFML");
  window.setFramerateLimit(144);
  // NOTE: This is due to me not handling each state for each key
  // I probably should in the future rework the InputManager to account for
  // previous frame state and store if the key was released, pressed or held
  // down however it works fine for me right now with my current event + polling
  // system
  window.setKeyRepeatEnabled(false);

  sf::Clock clock;
  clock.start();

  AssetManager assets;

  loadAssets(assets);

  InputManager inputManager;

  sf::Sprite player_sprite(assets.getTexture("player"));
  Player player(player_sprite);

  player.set_position(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));

  std::vector<sf::Sprite> floor_blocks;

  for (int i = 0; i < 15; i++) {
    sf::Sprite floor(assets.getTexture("grass"));
    floor.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f - 7 * 32 + i * 32,
                                   WINDOW_HEIGHT / 2.f + 96));
    floor_blocks.push_back(floor);
  }

  // temporary walls

  sf::Sprite wall(assets.getTexture("grass"));
  wall.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f + 120, WINDOW_HEIGHT / 2.f));
  sf::Sprite wall_two(assets.getTexture("grass"));
  wall_two.setPosition(
      sf::Vector2f(WINDOW_WIDTH / 2.f - 120, WINDOW_HEIGHT / 2.f));

  while (window.isOpen()) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
      if (event->is<sf::Event::KeyPressed>()) {
        inputManager.handleEvent(*event);
      }
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    inputManager.update();

    if (inputManager.isActionHeld(Action::MoveRight)) {
      player.set_acceleration(0.1f);
    } else if (inputManager.isActionHeld(Action::MoveLeft)) {
      player.set_acceleration(-0.1f);
    } else {
      player.set_acceleration(0.f);
    }

    // TODO: Implement jumping
    if (inputManager.isActionPressed(Action::Jump)) {
      std::cout << "Player jumped" << std::endl;
    }

    const int delta_time = clock.restart().asMilliseconds();

    player.check_horizontal_collisons(wall);
    player.check_horizontal_collisons(wall_two);

    window.clear(sf::Color(96, 152, 173));
    player.draw(window);
    player.update(delta_time);
    drawGroup(window, floor_blocks);
    window.draw(wall);
    window.draw(wall_two);
    window.display();

    inputManager.resetFrameState();
  }
}
