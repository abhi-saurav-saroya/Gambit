#pragma once
#include <SFML/Graphics.hpp>

class InputHandler {
public:
    static bool getBoardSquare(
        const sf::RenderWindow& window,
        int offsetX,
        int offsetY,
        int tileSize,
        int& row,
        int& col
    );
};