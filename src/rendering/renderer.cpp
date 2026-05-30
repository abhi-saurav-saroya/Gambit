#include "rendering/Renderer.hpp"
#include <iostream>

Renderer::Renderer() {
    // nothing yet
}

void Renderer::loadTextures() {
    std::vector<std::string> pieceNames = {
        "WhitePawn", "WhiteRook", "WhiteKnight", "WhiteBishop", "WhiteQueen", "WhiteKing",
        "BlackPawn", "BlackRook", "BlackKnight", "BlackBishop", "BlackQueen", "BlackKing"
    };

    for (const auto& piece : pieceNames) {
        std::string path = "assets/pieces/" + piece + ".png";

        sf::Texture texture;

        if (!texture.loadFromFile(path)) {
            std::cerr << "Failed to load: " << path << std::endl;
            continue;
        }

        textures[piece] = texture;
    }
}

void Renderer::loadFonts() {
    if (!font.openFromFile("assets/fonts/Poppins-SemiBold.ttf")) {
        std::cerr << "Failed to load font\n";
    }
}

void Renderer::render(sf::RenderWindow& window, const Board& board, int OFFSET_X, int OFFSET_Y, int TILE_SIZE) {
    const auto& grid = board.getGrid();
    
    // DRAW BOARD TILES
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {

            sf::RectangleShape tile(
                sf::Vector2f((float)TILE_SIZE, (float)TILE_SIZE)
            );

            tile.setPosition({
                (float)(OFFSET_X + col * TILE_SIZE),
                (float)(OFFSET_Y + row * TILE_SIZE)
            });

            if ((row + col) % 2 == 0)
                tile.setFillColor(sf::Color(240, 217, 181));
            else
                tile.setFillColor(sf::Color(181, 136, 99));

            window.draw(tile);
        }
    }

    // HIGHLIGHT SELECTED SQUARE
    if (board.hasSelection()) {
        auto [selRow, selCol] = board.getSelection();

        sf::RectangleShape highlight(
            sf::Vector2f((float)TILE_SIZE, (float)TILE_SIZE)
        );

        highlight.setPosition({
            (float)(OFFSET_X + selCol * TILE_SIZE),
            (float)(OFFSET_Y + selRow * TILE_SIZE)
        });

        highlight.setFillColor(sf::Color(80, 255, 120, 120));

        window.draw(highlight);
    }

    // HIGHLIGHT LEGAL MOVES
    for (const auto& move : board.getLegalMovesList()) {
        int moveRow = move.first;
        int moveCol = move.second;

        sf::CircleShape circle(TILE_SIZE / 6.f);

        circle.setFillColor(
            sf::Color(50, 50, 50, 180)
        );

        circle.setPosition({
            OFFSET_X + moveCol * TILE_SIZE + TILE_SIZE / 3.f,
            OFFSET_Y + moveRow * TILE_SIZE + TILE_SIZE / 3.f
        });

        window.draw(circle);
    }

    // DRAW PIECES
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {

            const std::string& piece = grid[row][col];

            if (!piece.empty() && textures.count(piece)) {

                sf::Sprite sprite(textures[piece]);

                sprite.setPosition({
                    (float)(OFFSET_X + col * TILE_SIZE),
                    (float)(OFFSET_Y + row * TILE_SIZE)
                });

                sf::Vector2u size = textures[piece].getSize();

                sprite.setScale({
                    (float)TILE_SIZE / size.x,
                    (float)TILE_SIZE / size.y
                });

                window.draw(sprite);
            }
        }
    }

    // PROMOTION OVERLAY
    if (board.isPromotionPending()) {
        sf::RectangleShape overlay(
            sf::Vector2f(
                (float)window.getSize().x,
                (float)window.getSize().y
            )
        );

        overlay.setFillColor(
            sf::Color(0, 0, 0, 180)
        );
        window.draw(overlay);

        sf::RectangleShape panel(
            sf::Vector2f(360.f, 420.f)
        );

        panel.setFillColor(
            sf::Color(40, 40, 40)
        );
        panel.setPosition({
            window.getSize().x / 2.f - 180.f,
            180.f
        });

        window.draw(panel);

        sf::Text title(font);
        title.setString("Choose Promotion");
        title.setCharacterSize(32);
        float titleWidth = title.getLocalBounds().size.x;
        title.setPosition({
            window.getSize().x / 2.f - titleWidth / 2.f,
            205.f
        });
        window.draw(title);

        // queen promotion button
        sf::RectangleShape queenButton(
            sf::Vector2f(220.f, 50.f)
        );
        queenButton.setPosition({
            window.getSize().x / 2.f - 110.f,
            270.f
        });
        queenButton.setFillColor(
            sf::Color(90, 90, 90)
        );
        window.draw(queenButton);
        sf::Text queenText(font);
        queenText.setString("Queen");
        queenText.setCharacterSize(24);
        float queenWidth = queenText.getLocalBounds().size.x;
        queenText.setPosition({
            window.getSize().x / 2.f - queenWidth / 2.f,
            280.f
        });
        window.draw(queenText);

        // rook promotion buttton
        sf::RectangleShape rookButton(
            sf::Vector2f(220.f, 50.f)
        );
        rookButton.setPosition({
            window.getSize().x / 2.f - 110.f,
            340.f
        });
        rookButton.setFillColor(
            sf::Color(90, 90, 90)
        );
        window.draw(rookButton);
        sf::Text rookText(font);
        rookText.setString("Rook");
        rookText.setCharacterSize(24);
        float rookWidth = rookText.getLocalBounds().size.x;
        rookText.setPosition({
            window.getSize().x / 2.f - rookWidth / 2.f,
            350.f
        });
        window.draw(rookText);

        // bishop promotion button
        sf::RectangleShape bishopButton(
            sf::Vector2f(220.f, 50.f)
        );
        bishopButton.setPosition({
            window.getSize().x / 2.f - 110.f,
            410.f
        });
        bishopButton.setFillColor(
            sf::Color(90, 90, 90)
        );
        window.draw(bishopButton);
        sf::Text bishopText(font);
        bishopText.setString("Bishop");
        bishopText.setCharacterSize(24);
        float bishopWidth = bishopText.getLocalBounds().size.x;
        bishopText.setPosition({
            window.getSize().x / 2.f - bishopWidth / 2.f,
            420.f
        });
        window.draw(bishopText);

        // knight promotion button
        sf::RectangleShape knightButton(
            sf::Vector2f(220.f, 50.f)
        );
        knightButton.setPosition({
            window.getSize().x / 2.f - 110.f,
            480.f
        });
        knightButton.setFillColor(
            sf::Color(90, 90, 90)
        );
        window.draw(knightButton);
        sf::Text knightText(font);
        knightText.setString("Knight");
        knightText.setCharacterSize(24);
        float knightWidth = knightText.getLocalBounds().size.x;
        knightText.setPosition({
            window.getSize().x / 2.f - knightWidth / 2.f,
            490.f
        });
        window.draw(knightText);
    }

    // CHECK OVERLAY
    if (board.isKingInCheck(board.isWhiteTurn())) {
        auto [kr, kc] = board.findKing(board.isWhiteTurn());

        sf::RectangleShape checkHighlight(
            sf::Vector2f((float)TILE_SIZE, (float)TILE_SIZE)
        );

        checkHighlight.setPosition({
            static_cast<float>(OFFSET_X + kc * TILE_SIZE),
            static_cast<float>(OFFSET_Y + kr * TILE_SIZE)
        });
        checkHighlight.setFillColor(sf::Color(255, 50, 50, 140));

        window.draw(checkHighlight);
    }
    
    // UI TEXT (TURN INDICATOR)
    sf::Text turnText(font);

    turnText.setString(
        board.isWhiteTurn() ? "White to Move" : "Black to Move"
    );

    turnText.setCharacterSize(28);
    turnText.setFillColor(sf::Color(180, 220, 255));

    // center above board
    float textWidth = turnText.getLocalBounds().size.x;
    turnText.setPosition({
        OFFSET_X + (TILE_SIZE * 8) / 2.f - textWidth / 2.f,
        OFFSET_Y - 45.f
    });

    window.draw(turnText);


    // GAME OVER OVERLAY
    if (board.isGameOver()) {

        // Dark transparent background
        sf::RectangleShape overlay(
            sf::Vector2f(
                static_cast<float>(window.getSize().x),
                static_cast<float>(window.getSize().y)
            )
        );

        overlay.setFillColor(
            sf::Color(0, 0, 0, 180)
        );

        window.draw(overlay);

        // CHECKMATE title
        sf::Text title(font);

        title.setString("CHECKMATE");

        title.setCharacterSize(56);

        title.setFillColor(sf::Color::White);

        float titleWidth =
            title.getLocalBounds().size.x;

        title.setPosition({
            window.getSize().x / 2.f - titleWidth / 2.f,
            220.f
        });

        window.draw(title);

        // Winner text
        sf::Text winnerText(font);

        winnerText.setString(
            board.getWinner() + " Wins!"
        );

        winnerText.setCharacterSize(34);

        winnerText.setFillColor(
            sf::Color(220, 220, 220)
        );

        float winnerWidth =
            winnerText.getLocalBounds().size.x;

        winnerText.setPosition({
            window.getSize().x / 2.f - winnerWidth / 2.f,
            310.f
        });

        window.draw(winnerText);

        // RESET BUTTON
        sf::RectangleShape resetButton(
            sf::Vector2f(220.f, 60.f)
        );

        resetButton.setPosition({
            window.getSize().x / 2.f - 110.f,
            430.f
        });

        resetButton.setFillColor(
            sf::Color(70, 180, 70)
        );

        window.draw(resetButton);

        sf::Text resetText(font);
        resetText.setString("Play Again");
        resetText.setCharacterSize(24);
        resetText.setFillColor(sf::Color::White);
        float resetWidth = resetText.getLocalBounds().size.x;

        resetText.setPosition({
            window.getSize().x / 2.f - resetWidth / 2.f,
            445.f
        });

        window.draw(resetText);

        // EXIT BUTTON
        sf::RectangleShape exitButton(
            sf::Vector2f(220.f, 60.f)
        );

        exitButton.setPosition({
            window.getSize().x / 2.f - 110.f,
            510.f
        });

        exitButton.setFillColor(
            sf::Color(180, 70, 70)
        );

        window.draw(exitButton);

        sf::Text exitText(font);
        exitText.setString("Exit");
        exitText.setCharacterSize(24);
        exitText.setFillColor(sf::Color::White);
        float exitWidth = exitText.getLocalBounds().size.x;

        exitText.setPosition({
            window.getSize().x / 2.f - exitWidth / 2.f,
            525.f
        });

        window.draw(exitText);
    } 

}