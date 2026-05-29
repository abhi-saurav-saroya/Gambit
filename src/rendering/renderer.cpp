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
}