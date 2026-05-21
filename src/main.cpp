#include <SFML/Graphics.hpp>

int main()
{
    const int WINDOW_SIZE = 800;
    const int TILE_SIZE = WINDOW_SIZE / 8;

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}),
        "Gambit"
    );

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        // Draw chessboard
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                sf::RectangleShape tile(
                    sf::Vector2f(
                        static_cast<float>(TILE_SIZE),
                        static_cast<float>(TILE_SIZE)
                    )
                );

                tile.setPosition(
                    {
                        static_cast<float>(col * TILE_SIZE),
                        static_cast<float>(row * TILE_SIZE)
                    }
                );

                // Alternate colors
                if ((row + col) % 2 == 0)
                    tile.setFillColor(sf::Color(240, 217, 181)); // light
                else
                    tile.setFillColor(sf::Color(181, 136, 99));  // dark

                window.draw(tile);
            }
        }

        window.display();
    }

    return 0;
}