#include <SFML/Graphics.hpp>
#include "core/Board.hpp"
#include "rendering/Renderer.hpp"
#include "input/InputHandler.hpp"
#include <iostream>
#include <string>

int main() {
    // WINDOW SETTINGS

    const int WINDOW_WIDTH  = 1200;
    const int WINDOW_HEIGHT = 900;

    const int BOARD_SIZE = 800;
    const int TILE_SIZE  = BOARD_SIZE / 8;

    const int OFFSET_X = (WINDOW_WIDTH  - BOARD_SIZE) / 2;
    const int OFFSET_Y = (WINDOW_HEIGHT - BOARD_SIZE) / 2;

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Gambit - Chess Engine"
    );

    // GAME OBJECTS
    Board board;
    Renderer renderer;

    renderer.loadTextures();
    renderer.loadFonts();


    // MAIN GAME LOOP
    while (window.isOpen()) {
        // EVENTS
        while (auto event = window.pollEvent()) {
            // Close window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // MOUSE CLICK
            if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouse->button == sf::Mouse::Button::Left) {
                    int row, col;

                    // click inside board?
                    if (InputHandler::getBoardSquare(
                        window,
                        OFFSET_X,
                        OFFSET_Y,
                        TILE_SIZE,
                        row,
                        col))
                    {
                        // NO PIECE CURRENTLY SELECTED
                        if (!board.hasSelection()) {

                            std::string piece = board.getGrid()[row][col];

                            // non-empty square
                            if (!piece.empty()) {
                                bool isWhitePiece = (piece[0] == 'W');

                                // White's turn
                                if (board.isWhiteTurn() && isWhitePiece) {
                                    board.selectSquare(row, col);
                                    auto pseudoMoves = board.getLegalMoves(row, col);
                                    std::vector<std::pair<int,int>> legalMoves;
                                    for (auto [r, c] : pseudoMoves) {
                                        if (board.isLegalMove(row, col, r, c)) {
                                            legalMoves.push_back({r, c});
                                        }
                                    }
                                    board.setLegalMoves(legalMoves);
                                }

                                // Black's turn
                                else if (!board.isWhiteTurn() && !isWhitePiece) {
                                    board.selectSquare(row, col);
                                    auto pseudoMoves = board.getLegalMoves(row, col);
                                    std::vector<std::pair<int,int>> legalMoves;
                                    for (auto [r, c] : pseudoMoves) {
                                        if (board.isLegalMove(row, col, r, c)) {
                                            legalMoves.push_back({r, c});
                                        }
                                    }
                                    board.setLegalMoves(legalMoves);
                                }
                            }
                        }

                        // PIECE ALREADY SELECTED
                        else {
                            auto [selRow, selCol] = board.getSelection();

                            // legal move?
                            if (board.isLegalMove(selRow, selCol, row, col)) {
                                board.movePiece(selRow, selCol, row, col);
                                board.clearSelection();
                                board.clearLegalMoves();
                                board.switchTurn();
                                if (board.isCheckmate(board.isWhiteTurn())) {
                                    board.setGameOver(board.isWhiteTurn() ? "Black" : "White");
                                }
                            }

                            // CLICKED ANOTHER SQUARE
                            else {
                                board.clearSelection();
                                board.clearLegalMoves();

                                std::string piece = board.getGrid()[row][col];

                                if (!piece.empty()) {
                                    bool isWhitePiece = (piece[0] == 'W');
                                    // White's turn
                                    if (board.isWhiteTurn() && isWhitePiece) {
                                        board.selectSquare(row, col);
                                        auto pseudoMoves = board.getLegalMoves(row, col);
                                        std::vector<std::pair<int,int>> legalMoves;
                                        for (auto [r, c] : pseudoMoves) {
                                            if (board.isLegalMove(row, col, r, c)) {
                                                legalMoves.push_back({r, c});
                                            }
                                        }
                                        board.setLegalMoves(legalMoves);
                                    }

                                    // Black's turn
                                    else if (!board.isWhiteTurn() && !isWhitePiece){
                                        board.selectSquare(row, col);
                                        auto pseudoMoves = board.getLegalMoves(row, col);
                                        std::vector<std::pair<int,int>> legalMoves;
                                        for (auto [r, c] : pseudoMoves) {
                                            if (board.isLegalMove(row, col, r, c)) {
                                                legalMoves.push_back({r, c});
                                            }
                                        }
                                        board.setLegalMoves(legalMoves);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // RENDERING
        window.clear();
        renderer.render(
            window,
            board,
            OFFSET_X,
            OFFSET_Y,
            TILE_SIZE
        );

        window.display();
    }

    return 0;
}