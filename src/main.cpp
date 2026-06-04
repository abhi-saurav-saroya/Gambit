#include <SFML/Graphics.hpp>
#include "core/Board.hpp"
#include "rendering/Renderer.hpp"
#include "input/InputHandler.hpp"
#include <iostream>
#include <string>

int main() {
    // WINDOW SETTINGS

    const int WINDOW_WIDTH  = 1500;
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

            // CLOSE WINDOW
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // MOUSE CLICK
            if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {

                if (board.isPromotionPending()) {
                    int mouseX = mouse->position.x;
                    int mouseY = mouse->position.y;

                    int centerX = WINDOW_WIDTH / 2;
                    bool whitePromotion = board.isPromotionWhite();

                    std::string prefix = whitePromotion ? "White" : "Black";

                    if (mouseX >= centerX - 110 && mouseX <= centerX + 110 && mouseY >= 270 && mouseY <= 320) {
                        board.promoteTo(prefix + "Queen");
                        continue;
                    }

                    if (mouseX >= centerX - 110 && mouseX <= centerX + 110 && mouseY >= 340 && mouseY <= 390) {
                        board.promoteTo(prefix + "Rook");
                        continue;
                    }

                    if (mouseX >= centerX - 110 && mouseX <= centerX + 110 && mouseY >= 480 && mouseY <= 530) {
                        board.promoteTo(prefix + "Knight");
                        continue;
                    }
        
                    if (mouseX >= centerX - 110 && mouseX <= centerX + 110 && mouseY >= 410 && mouseY <= 460) {
                        board.promoteTo(prefix + "Bishop");
                        continue;
                    }

                    continue;
                }

                if (mouse->button == sf::Mouse::Button::Left) {

                    int mouseX = mouse->position.x;
                    int mouseY = mouse->position.y;

                    // RESIGN BUTTON
                    float historyX = 20.f;
                    float historyY = OFFSET_Y + 100.f;

                    if (!board.isGameOver()) {
                    
                        if (mouseX >= historyX + 20.f &&
                            mouseX <= historyX + 200.f &&
                            mouseY >= historyY + 620.f &&
                            mouseY <= historyY + 670.f)
                        {
                            if (board.isWhiteTurn()) {
                                board.setGameOver("Black", "Resignation");
                            }
                            else {
                                board.setGameOver("White", "Resignation");
                            }
                        
                            continue;
                        }
                    }

                    // GAME OVER BUTTONS
                    if (board.isGameOver()) {
                        int centerX = WINDOW_WIDTH / 2;

                        // PLAY AGAIN BUTTON
                        if (mouseX >= centerX - 110 &&
                            mouseX <= centerX + 110 &&
                            mouseY >= 430 &&
                            mouseY <= 490) 
                        {
                            board.resetGame();
                            continue;
                        }

                        // EXIT BUTTON
                        if (mouseX >= centerX - 110 &&
                            mouseX <= centerX + 110 &&
                            mouseY >= 510 &&
                            mouseY <= 570)
                        {
                            window.close();
                            continue;
                        }

                        continue;
                    }

                    int row, col;

                    // CLICK INSIDE BOARD?
                    if (InputHandler::getBoardSquare(
                        window,
                        OFFSET_X,
                        OFFSET_Y,
                        TILE_SIZE,
                        row,
                        col))
                    {
                        // NO PIECE SELECTED
                        if (!board.hasSelection()) {
                            if (board.canSelectPiece(row, col)) {
                                board.selectPiece(row, col);
                            }
                        }

                        // PIECE ALREADY SELECTED
                        else {
                            auto [selRow, selCol] = board.getSelection();
                            // legal move
                            if (board.isLegalMove(selRow, selCol, row, col)) {
                                board.movePiece(selRow, selCol, row, col);
                                board.checkPromotion();
                                board.clearSelection();
                                board.clearLegalMoves();
                                board.switchTurn();
                            
                                if (board.isCheckmate(board.isWhiteTurn())) {
                                    board.setGameOver(
                                        board.isWhiteTurn() ? "Black" : "White",
                                        "Checkmate"
                                    );
                                }

                                else if (board.isStalemate(board.isWhiteTurn())) {
                                    board.setGameOver(
                                        "Draw",
                                        "Stalemate"
                                    );
                                }
                            }
                        
                            // clicked somewhere else
                            else {
                                board.clearSelection();
                                board.clearLegalMoves();
                            
                                if (board.canSelectPiece(row, col)) {
                                    board.selectPiece(row, col);
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