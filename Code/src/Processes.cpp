#include <Processes.hpp>
#include <Globals.hpp>

bool logicProcess() {
    events.clear();
    for (sf::Event ev; window->pollEvent(ev);) {
        if (ev.type == sf::Event::Closed) { return false; }
        events.push_back(ev);
    }
    for (auto object: logic_pipeline) { object->logicProcess(); }
    return !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}

void physicsProcess() {
    for (auto object: physics_pipeline) { object->physicsProcess(); }
}

void renderProcess() {
    window->clear(sf::Color::Black);

    for (auto object: render_pipeline) { object->renderProcess(); }

    window->display();
}
