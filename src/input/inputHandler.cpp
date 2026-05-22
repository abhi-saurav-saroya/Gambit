#include "input/InputHandler.hpp"

bool InputHandler::getBoardSquare(
    const sf::RenderWindow& window,
    int offsetX,
    int offsetY,
    int tileSize,
    int& row,
    int& col)
{
    auto mousePos = sf::Mouse::getPosition(window);

    col = (mousePos.x - offsetX) / tileSize;
    row = (mousePos.y - offsetY) / tileSize;

    return (row >= 0 && row < 8 && col >= 0 && col < 8);
}