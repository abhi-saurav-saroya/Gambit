#include <SFML/Graphics.hpp>
#include <optional>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800u, 800u}), "Gambit");

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}