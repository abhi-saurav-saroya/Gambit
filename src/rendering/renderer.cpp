#include "rendering/Renderer.hpp"
#include <iostream>

Renderer::Renderer() {
    // nothing yet
}

void Renderer::loadTextures() {
    std::vector<std::string> pieceNames = {
        "WhitePawn",
        "WhiteRook",
        "WhiteKnight",
        "WhiteBishop",
        "WhiteQueen",
        "WhiteKing",

        "BlackPawn",
        "BlackRook",
        "BlackKnight",
        "BlackBishop",
        "BlackQueen",
        "BlackKing"
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

void Renderer::render(sf::RenderWindow& window, const Board& board, int OFFSET_X, int OFFSET_Y, int TILE_SIZE) {
    // draw board
    const auto& grid = board.getGrid();
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            sf::RectangleShape tile(
                sf::Vector2f(
                    static_cast<float>(TILE_SIZE),
                    static_cast<float>(TILE_SIZE)
                )
            );

            tile.setPosition({
                static_cast<float>(OFFSET_X + col * TILE_SIZE),
                static_cast<float>(OFFSET_Y + row * TILE_SIZE)
            });

            if ((row + col) % 2 == 0)
                tile.setFillColor(sf::Color(240, 217, 181));
            else
                tile.setFillColor(sf::Color(181, 136, 99));

            window.draw(tile);

            // highlight selected tile
            if (board.hasSelection()) {
                auto [selRow, selCol] = board.getSelection();

                if (row == selRow && col == selCol) {
                    sf::RectangleShape highlight(
                        sf::Vector2f(
                            static_cast<float>(TILE_SIZE),
                            static_cast<float>(TILE_SIZE)
                        )
                    );

                    highlight.setPosition({
                        static_cast<float>(OFFSET_X + col * TILE_SIZE),
                        static_cast<float>(OFFSET_Y + row * TILE_SIZE)
                    });

                    highlight.setFillColor(sf::Color(80, 255, 120, 120));

                    window.draw(highlight);
                }
            }

            // draw piece
            const std::string& piece = grid[row][col];

            if (!piece.empty() && textures.count(piece)) {
                sf::Sprite sprite(textures[piece]);

                sprite.setPosition({
                    static_cast<float>(OFFSET_X + col * TILE_SIZE),
                    static_cast<float>(OFFSET_Y + row * TILE_SIZE)
                });

                sf::Vector2u size = textures[piece].getSize();

                sprite.setScale({
                    static_cast<float>(TILE_SIZE) / size.x,
                    static_cast<float>(TILE_SIZE) / size.y
                });

                window.draw(sprite);
            }
        }
    }
}