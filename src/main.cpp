#include <SFML/Graphics.hpp>

int main() {
    // Window settings
    const int WINDOW_WIDTH  = 1200;
    const int WINDOW_HEIGHT = 900;

    // Chessboard settings
    const int BOARD_SIZE = 800;
    const int TILE_SIZE  = BOARD_SIZE / 8;

    // Center board
    const int BOARD_OFFSET_X = (WINDOW_WIDTH - BOARD_SIZE) / 2;
    const int BOARD_OFFSET_Y = (WINDOW_HEIGHT - BOARD_SIZE) / 2;

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Gambit - Chess Engine"
    );

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Background color
        window.clear(sf::Color(30, 30, 30));

        // Board border
        sf::RectangleShape border(
            sf::Vector2f(
                static_cast<float>(BOARD_SIZE + 8),
                static_cast<float>(BOARD_SIZE + 8)
            )
        );

        border.setPosition({
            static_cast<float>(BOARD_OFFSET_X - 4),
            static_cast<float>(BOARD_OFFSET_Y - 4)
        });

        border.setFillColor(sf::Color(80, 80, 80));

        window.draw(border);

        // Draw chessboard
        for (int row = 0; row < 8; row++)
        {
            for (int col = 0; col < 8; col++)
            {
                sf::RectangleShape tile(
                    sf::Vector2f(
                        static_cast<float>(TILE_SIZE),
                        static_cast<float>(TILE_SIZE)
                    )
                );

                tile.setPosition({
                    static_cast<float>(BOARD_OFFSET_X + col * TILE_SIZE),
                    static_cast<float>(BOARD_OFFSET_Y + row * TILE_SIZE)
                });

                // Chess colors
                if ((row + col) % 2 == 0)
                    tile.setFillColor(sf::Color(240, 217, 181));
                else
                    tile.setFillColor(sf::Color(181, 136, 99));

                window.draw(tile);
            }
        }

        window.display();
    }

    return 0;
}