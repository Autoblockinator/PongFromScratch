#include <SFML/Graphics.hpp>
#include <iostream>

#include "node.cpp"

void is_node_root(Node* node)
{
    if (node->parent == nullptr) { std::cout << "Node is root." << std::endl; }
    else { std::cout << "Node is not root." << std::endl; }
}

int main()
{
    auto window = sf::RenderWindow{{1920, 1080}, "Pong"};
    window.setFramerateLimit(144);

    Node root;
    Node child;

    root.parent = nullptr;
    root.add_child(&child);

    is_node_root(&root);
    is_node_root(&child);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        auto rect = sf::RectangleShape({20, 100});
        rect.setPosition({50, 50});
        rect.setFillColor(sf::Color::White);
        window.draw(rect);

        window.display();
    }

    return 0;
}