#include <Processes.hpp>

bool logicProcess(
    const std::vector<I_LogicProcess*> &pipeline,
    float &delta,
    sf::RenderWindow &window
) {
    std::vector<sf::Event> ev_list{};
    for (sf::Event ev; window.pollEvent(ev);) {
        if (ev.type == sf::Event::Closed) { return false; }
        ev_list.push_back(ev);
    }
    for (auto object: pipeline) {
        for (auto ev: ev_list) { object->logicProcess(ev, delta); }
    }
    return !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}

void physicsProcess(
    std::vector<I_PhysicsProcess*> &pipeline,
    float &delta
) {
    for (const auto object: pipeline) { object->physicsProcess(pipeline, delta); }
}

void renderProcess(
    const std::vector<I_RenderProcess*> &pipeline,
    sf::RenderWindow &window,
    const float &delta
) {
    window.clear(sf::Color::Black);

    for (const auto object: pipeline) { object->renderProcess(window, delta); }

    window.display();
}
