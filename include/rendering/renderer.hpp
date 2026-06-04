#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <optional>
#include <string>
#include "core/Board.hpp"

class Renderer {
public:
    Renderer();

    void loadTextures();
    void loadFonts();
    void loadSounds();
    void playMoveSound();

    void render(
        sf::RenderWindow& window,
        const Board& board,
        int offsetX,
        int offsetY,
        int tileSize
    );

private:
    std::map<std::string, sf::Texture> textures;
    sf::Font font;
    sf::SoundBuffer moveBuffer;
    std::optional<sf::Sound> moveSound;
};