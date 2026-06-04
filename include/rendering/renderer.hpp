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
    void playCaptureSound();
    void playCheckSound();

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

    sf::SoundBuffer captureBuffer;
    std::optional<sf::Sound> captureSound;

    sf::SoundBuffer checkBuffer;
    std::optional<sf::Sound> checkSound;
};