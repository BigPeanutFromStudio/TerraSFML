#include <SFML/Graphics.hpp>
#include <AssetManager.h>
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

    AssetManager assets;

    loadAssets(assets);

    sf::Sprite player(assets.getTexture("player"));
    player.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

    std::vector<sf::Sprite> floor_blocks;

    for (int i = 0; i < 15; i++)
    {
        sf::Sprite floor(assets.getTexture("grass"));
        floor.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 7 * 32 + i * 32, WINDOW_HEIGHT / 2 + 96));
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

        window.clear(sf::Color::Color(96, 152, 173));
        window.draw(player);
        drawGroup(window, floor_blocks);
        window.display();
    }
}
