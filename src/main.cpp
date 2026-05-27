#include <SFML/Graphics.hpp>
#include "core/Board.hpp"
#include "rendering/Renderer.hpp"
#include "input/InputHandler.hpp"
#include <iostream>

int main() {
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 900;

    const int BOARD_SIZE = 800;
    const int TILE_SIZE = BOARD_SIZE / 8;

    const int OFFSET_X = (WINDOW_WIDTH - BOARD_SIZE) / 2;
    const int OFFSET_Y = (WINDOW_HEIGHT - BOARD_SIZE) / 2;

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Gambit - Chess Engine"
    );

    Board board;
    Renderer renderer;

    renderer.loadTextures();
    renderer.loadFonts();

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse->button == sf::Mouse::Button::Left) {
                    int row, col;

                    if (InputHandler::getBoardSquare(
                        window,
                        OFFSET_X,
                        OFFSET_Y,
                        TILE_SIZE,
                        row,
                        col))
                    {
                        // SELECTION LOGIC
                        if (board.hasSelection()) {
                            auto [selectedRow, selectedCol] = board.getSelection();
                            if (board.isLegalMove(selectedRow, selectedCol, row, col)) {
                                board.movePiece(selectedRow, selectedCol, row, col);
                                board.switchTurn();
                            }
                            board.clearSelection();
                        } else {
                            if (!board.getGrid()[row][col].empty()) {
                                if (board.isCurrentPlayersPiece(row, col)) {
                                    board.selectSquare(row, col);
                                }
                            }
                        }
                    }
                }
            }
        }

        window.clear();

        renderer.render(window, board, OFFSET_X, OFFSET_Y, TILE_SIZE);
        window.display();
    }

    return 0;
}