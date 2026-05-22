#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "core/Board.hpp"

class Renderer {
public:
    Renderer();

    void loadTextures();

    void render(
        sf::RenderWindow& window,
        const Board& board
    );

private:
    std::map<std::string, sf::Texture> textures;
};