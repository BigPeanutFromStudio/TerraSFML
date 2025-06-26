#include <SFML/Graphics.hpp>
#include <AssetManager.h>
#include <Player.h>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

void loadAssets(AssetManager &assetManager)
{
    assetManager.loadTexture("grass", "./assets/grass.png");
    assetManager.loadTexture("dirt", "./assets/dirt.png");
    assetManager.loadTexture("player", "./assets/player.png");
}

void drawGroup(sf::RenderWindow &window, const std::vector<sf::Sprite> &group)
{
    for (sf::Sprite sprite : group)
    {
        window.draw(sprite);
    }
}



int main()
{

    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;

    auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "TerraSFML");
    window.setFramerateLimit(144);

    sf::Clock clock;
    clock.start();

    AssetManager assets;

    loadAssets(assets);

    sf::Sprite player_sprite(assets.getTexture("player"));
    Player player(player_sprite);
    
    player.set_position(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));
    player.apply_velocity(sf::Vector2f(0.1f, 0.1f));

    std::vector<sf::Sprite> floor_blocks;

    for (int i = 0; i < 15; i++)
    {
        sf::Sprite floor(assets.getTexture("grass"));
        floor.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f - 7 * 32 + i * 32, WINDOW_HEIGHT / 2.f + 96));
        floor_blocks.push_back(floor);
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        const int delta_time = clock.restart().asMilliseconds();

        window.clear(sf::Color(96, 152, 173));
        player.draw(window);
        player.update(delta_time);
        drawGroup(window, floor_blocks);
        window.display();
    }
}
