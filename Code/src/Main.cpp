#include <SFML/Graphics.hpp>
#include <Utils/All.h>
#include <Paddle.h>

int main()
{
    auto window = sf::RenderWindow{{1920, 1080}, "Pong"};
    window.setFramerateLimit(144);

    sf::Clock clock;
    sf::Time delta;

    while (true)
    {
        window.clear(sf::Color::Black);

        for (sf::Event event; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed) { window.close(); }
        }
        if (!window.isOpen()) { break; }

        auto rect = sf::RectangleShape({20, 100});
        rect.setPosition({50, 50});
        rect.setFillColor(sf::Color::White);
        window.draw(rect);

        auto rect2 = sf::RectangleShape({20,100});
        rect2.setPosition({static_cast<float>(window.getSize().x-(50+20)), 50});
        rect2.setFillColor(sf::Color::White);
        window.draw(rect2);

        window.display();
    }

    return 0;
}