#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow{{1920u, 1080u}, "Pong"};
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        window.clear();

        auto rect = sf::RectangleShape({20, 100});
        rect.setPosition({50, 50});
        rect.setFillColor(sf::Color::White);
        window.draw(rect);

        window.display();
    }

    return 0;
}