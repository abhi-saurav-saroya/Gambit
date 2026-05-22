#include <SFML/Graphics.hpp>
#include "core/Board.hpp"
#include "rendering/Renderer.hpp"
#include "input/InputHandler.hpp"
#include <iostream>

int main()
{
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 900;

    const int BOARD_SIZE = 800;
    const int TILE_SIZE = BOARD_SIZE / 8;

    const int OFFSET_X = (WINDOW_WIDTH - BOARD_SIZE) / 2;
    const int OFFSET_Y = (WINDOW_HEIGHT - BOARD_SIZE) / 2;

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Gambit"
    );

    Board board;
    Renderer renderer;

    renderer.loadTextures();

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* mouse =
                event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouse->button == sf::Mouse::Button::Left)
                {
                    int row, col;

                    if (InputHandler::getBoardSquare(
                        window,
                        OFFSET_X,
                        OFFSET_Y,
                        TILE_SIZE,
                        row,
                        col))
                    {
                        std::cout << row << " " << col << "\n";
                    }
                }
            }
        }

        window.clear();

        renderer.render(window, board);

        window.display();
    }
}