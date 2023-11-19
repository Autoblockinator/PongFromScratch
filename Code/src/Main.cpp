#include <SFML/Graphics.hpp>

#include "Utils/All.h"
#include "Interfaces.cpp"
#include "Collider.cpp"
#include "Paddle.cpp"
#include "Ball.cpp"

bool logicProcess(
    const std::vector<I_LogicProcess*> &pipeline,
    float &delta,
    sf::RenderWindow &window
) {
    // for (const auto object: pipeline) {
        for (sf::Event ev; window.pollEvent(ev);) {
            if (ev.type == sf::Event::Closed) { return false; }
            // if (!object->logicProcess(ev, delta)) { return false; }
        }
    // }
    return !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}

void physicsProcess(
    const std::vector<I_PhysicsProcess*> &pipeline,
    float &delta
) {
    for (const auto object: pipeline) { object->physicsProcess(delta); }
}

void renderProcess(
    const std::vector<I_RenderProcess*> &pipeline,
    sf::RenderWindow &window
) {
    window.clear(sf::Color::Black);

    for (const auto drawable: pipeline) { drawable->renderProcess(window); }

    window.display();
}

int main() {
    sf::RenderWindow window{{1920, 1080}, "Pong"};
    window.setFramerateLimit(144);
    sf::Clock clock{};

    std::vector<I_LogicProcess*> logic_pipeline{};
    std::vector<I_PhysicsProcess*> physics_pipeline{};
    std::vector<I_RenderProcess*> render_pipeline{};
    std::vector<Collider*> colliders{};

    Paddle player_1{true, &window};
    physics_pipeline.push_back(&player_1);
    render_pipeline.push_back(&player_1);
    
    Paddle player_2{false, &window};
    physics_pipeline.push_back(&player_2);
    render_pipeline.push_back(&player_2);

    Ball ball{&window};
    physics_pipeline.push_back(&ball);
    render_pipeline.push_back(&ball);

    for (
        float delta = clock.restart().asSeconds();
        logicProcess(logic_pipeline, delta, window);
    ) {

        //

        physicsProcess(physics_pipeline, delta);
        renderProcess(render_pipeline, window);
    }

    window.close();
    return 0;
}