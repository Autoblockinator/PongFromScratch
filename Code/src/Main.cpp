#include <SFML/Graphics.hpp>

#include "Utils/All.h"
#include "Interfaces.cpp"
#include "Paddle.cpp"

bool logicProcess(const std::vector<I_LogicProcess*> &pipeline, float &delta, sf::RenderWindow &window) {
    for (sf::Event event; window.pollEvent(event);) {
        if (event.type == sf::Event::Closed) { return false; }
    }
    return true;
}

void physicsProcess(const std::vector<I_PhysicsProcess*> &pipeline, float &delta) {}

void renderProcess(const std::vector<I_RenderProcess*> &pipeline, sf::RenderWindow &window) {
    using sf::Color;

    window.clear(Color(Color::Black));

    for (const auto drawable: pipeline) { drawable->renderProcess(window); }

    // auto rect = sf::RectangleShape({20, 100});
    // rect.setPosition({50, 50});
    // rect.setFillColor(sf::Color::White);
    // window.draw(rect);

    // auto rect2 = sf::RectangleShape({20,100});
    // rect2.setPosition({static_cast<float>(window.getSize().x-(50+20)), 50});
    // rect2.setFillColor(sf::Color::White);
    // window.draw(rect2);

    window.display();
}

int main() {
    sf::RenderWindow window{{1920, 1080}, "Pong"};
    window.setFramerateLimit(144);
    sf::Clock clock;

    Paddle player_1{};
    Paddle player_2{};

    std::vector<I_LogicProcess*> logic_pipeline{};
    std::vector<I_PhysicsProcess*> physics_pipeline{};
    std::vector<I_RenderProcess*> render_pipeline{};

    for (float delta = clock.restart().asSeconds(); logicProcess(logic_pipeline, delta, window);) {
        physicsProcess(physics_pipeline, delta);
        renderProcess(render_pipeline, window);
    }
    window.close();

    return 0;
}