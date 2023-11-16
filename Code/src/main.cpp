#include <SFML/Graphics.hpp>
#include <iostream>

#include "node.cpp"

int main()
{
    auto window = sf::RenderWindow{{1920, 1080}, "Pong"};
    window.setFramerateLimit(144);

    Node root;
    Node child;

    while (true)
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed) { window.close(); }
        }
        if (!window.isOpen()) { break; }

        window.clear(sf::Color::Black);

        auto rect = sf::RectangleShape({20, 100});
        rect.setPosition({50, 50});
        rect.setFillColor(sf::Color::White);
        window.draw(rect);

        window.display();
    }

    return 0;
}