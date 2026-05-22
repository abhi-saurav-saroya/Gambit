#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>
#include <iostream>

int main() {
    // Window settings
    const int WINDOW_WIDTH  = 1200;
    const int WINDOW_HEIGHT = 900;

    // Board settings
    const int BOARD_SIZE = 800;
    const int TILE_SIZE  = BOARD_SIZE / 8;

    const int OFFSET_X = (WINDOW_WIDTH - BOARD_SIZE) / 2;
    const int OFFSET_Y = (WINDOW_HEIGHT - BOARD_SIZE) / 2;

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Gambit"
    );

    // Board representation
    std::vector<std::vector<std::string>> board = {
        {
            "BlackRook",
            "BlackKnight",
            "BlackBishop",
            "BlackQueen",
            "BlackKing",
            "BlackBishop",
            "BlackKnight",
            "BlackRook"
        },
        {
            "BlackPawn",
            "BlackPawn",
            "BlackPawn",
            "BlackPawn",
            "BlackPawn",
            "BlackPawn",
            "BlackPawn",
            "BlackPawn"
        },
        {"","","","","","","",""},
        {"","","","","","","",""},
        {"","","","","","","",""},
        {"","","","","","","",""},
        {
            "WhitePawn",
            "WhitePawn",
            "WhitePawn",
            "WhitePawn",
            "WhitePawn",
            "WhitePawn",
            "WhitePawn",
            "WhitePawn"
        },
        {
            "WhiteRook",
            "WhiteKnight",
            "WhiteBishop",
            "WhiteQueen",
            "WhiteKing",
            "WhiteBishop",
            "WhiteKnight",
            "WhiteRook"
        }
    };

    // Load textures
    std::map<std::string, sf::Texture> textures;

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
        if (!textures[piece].loadFromFile(path)) {
            return -1;
        }
    }

    // Main loop
    while (window.isOpen()){
        while (auto event = window.pollEvent()) {
            // Close window
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            
            // Mouse click
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    auto mousePos = sf::Mouse::getPosition(window);
                    int col = (mousePos.x - OFFSET_X) / TILE_SIZE;
                    int row = (mousePos.y - OFFSET_Y) / TILE_SIZE;
                    if (row >= 0 && row < 8 && col >= 0 && col < 8) {
                        std::cout << "Row: " << row << " Col: " << col << std::endl;
                    } else {
                        std::cout << "Invalid Square" << std::endl;
                    } 
                }
            }
        }

        // Background
        window.clear(sf::Color(30, 30, 30));

        // Border
        sf::RectangleShape border(
            sf::Vector2f(
                static_cast<float>(BOARD_SIZE + 8),
                static_cast<float>(BOARD_SIZE + 8)
            )
        );

        border.setPosition({
            static_cast<float>(OFFSET_X - 4),
            static_cast<float>(OFFSET_Y - 4)
        });

        border.setFillColor(sf::Color(80, 80, 80));

        window.draw(border);

        // Draw board + pieces
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                // Draw tile
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

                // Draw piece
                std::string piece = board[row][col];

                if (piece != "") {
                    sf::Sprite sprite(textures[piece]);

                    sprite.setPosition({
                        static_cast<float>(OFFSET_X + col * TILE_SIZE),
                        static_cast<float>(OFFSET_Y + row * TILE_SIZE)
                    });

                    // Scale piece to fit tile
                    sf::Vector2u textureSize =
                        textures[piece].getSize();

                    sprite.setScale({
                        static_cast<float>(TILE_SIZE) / textureSize.x,
                        static_cast<float>(TILE_SIZE) / textureSize.y
                    });

                    window.draw(sprite);
                }
            }
        }

        window.display();

        // if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        //     auto mousePos = sf::Mouse::getPosition(window);
        //     int col = (mousePos.x - OFFSET_X) / TILE_SIZE;
        //     int row = (mousePos.y - OFFSET_Y) / TILE_SIZE;

        //     if (row >= 0 && row < 8 && col >= 0 && col < 8)
        //         std::cout << "row " << row << " col" << col << std::endl;
        //     else
        //         std::cout << "Invalid Square" << std::endl;
        // }

    }

    return 0;
}